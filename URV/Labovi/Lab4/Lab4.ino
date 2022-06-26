#include <EEPROM.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int BUTTON_LEFT = 2;
const int BUTTON_CENTER = 3;
const int BUTTON_RIGHT = 4;
const int LED_LEFT = 5;
const int LED_CENTER = 6;
const int LED_RIGHT = 7;
const int ANALOG_IN = A0;
const int ANALOG_OUT = 11;
const double Ts = 0.02;
const int PARAM_ADDR_W = 0;
const int PARAM_ADDR_Kp = 1;
const int PARAM_ADDR_Ti = 5;
const int PARAM_ADDR_SL = 9;
const int PARAM_ADDR_SH = 13;
const unsigned char EEPROM_W = 53;
const double DEFAULT_Kp = 0.45;
const double DEFAULT_Ti = 0.15;
const int DEFAULT_SL = 100;
const int DEFAULT_SH = 1010;
const int BUTTON_PINS[] = {BUTTON_LEFT, BUTTON_CENTER, BUTTON_RIGHT};
const int DEBOUNCE_THRESHOLD = 50;
const int HOLD_THRESHOLD = 1000;
const int HOLD_REPEAT = 250;

LiquidCrystal_I2C lcd(0x27, 16, 2);

double Kp;
double Ti;
int SL;
int SH;
bool flagParams = false;
int counterLCD = 0;
bool manual = true;
double reference = 0;
double control = 0;
double measurement;
double error;
double control_p;
double control_i;
int buttonStates[3] = {LOW, LOW, LOW};
unsigned long debounceTimers[3] = {0};
bool repeating[3] = {0};
char sprintfStr[255];
char float1Str[10];
char float2Str[10];
char float3Str[10];
char float4Str[10];

double smart_map(double x, double in_min, double in_max, double out_min, double out_max) {
  double result = (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
  if (result < out_min) {
    return out_min;
  }
  if (result > out_max) {
    return out_max;
  }
  return result;
}

void updateLED() {
  if (manual) {
    digitalWrite(LED_LEFT, LOW);
    digitalWrite(LED_CENTER, HIGH);
    digitalWrite(LED_RIGHT, LOW);
  } else {
    digitalWrite(LED_LEFT, HIGH);
    digitalWrite(LED_CENTER, LOW);
    digitalWrite(LED_RIGHT, HIGH);
  }
}

void setup() {
  // Serial
  Serial.begin(115200);
  // LCD
  lcd.init();
  lcd.backlight();
  // LED
  pinMode(LED_LEFT, OUTPUT);
  pinMode(LED_CENTER, OUTPUT);
  pinMode(LED_RIGHT, OUTPUT);
  updateLED();
  // Buttons
  pinMode(BUTTON_LEFT, INPUT);
  pinMode(BUTTON_CENTER, INPUT);
  pinMode(BUTTON_RIGHT, INPUT);
  // Sensors
  pinMode(ANALOG_IN, INPUT);
  pinMode(ANALOG_OUT, OUTPUT);
  // EEPROM
  if (EEPROM[PARAM_ADDR_W] != EEPROM_W) {
    EEPROM.put(PARAM_ADDR_W, EEPROM_W);
    Kp = DEFAULT_Kp;
    Ti = DEFAULT_Ti;
    SL = DEFAULT_SL;
    SH = DEFAULT_SH;
    EEPROM.put(PARAM_ADDR_Kp, Kp);
    EEPROM.put(PARAM_ADDR_Ti, Ti);
    EEPROM.put(PARAM_ADDR_SL, SL);
    EEPROM.put(PARAM_ADDR_SH, SH);
    // Serial.println("Written to EEPROM.");
  } else {
    EEPROM.get(PARAM_ADDR_Kp, Kp);
    EEPROM.get(PARAM_ADDR_Ti, Ti);
    EEPROM.get(PARAM_ADDR_SL, SL);
    EEPROM.get(PARAM_ADDR_SH, SH);
    Serial.println("Read from EEPROM:");
    Serial.print("Kp = ");
    Serial.println(Kp);
    Serial.print("Ti = ");
    Serial.println(Ti);
    Serial.print("SL = ");
    Serial.println(SL);
    Serial.print("SH = ");
    Serial.println(SH);
  }
  // Timer1
  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  // 50Hz = 16MHz / 256 / 1250
  OCR1A = 1250;
  // CTC = on, prescaler = 256
  TCCR1B |= (1 << WGM12) | (1 << CS12);
  // Enable interrupt
  TIMSK1 |= (1 << OCIE1A);
  sei();
}

void loop() {
  // PID
  if (flagParams) {
    measurement = smart_map(analogRead(ANALOG_IN), SL, SH, 0, 100);
    if (manual) {
      reference = measurement;
    } else {
      error = reference - measurement;
      control_p = Kp * error;
      control_i += Kp * Ti * Ts * error;
      control = constrain(control_p + control_i, 0, 100);
      if (control == 100) {
        control_i -= Kp * Ti * Ts * error;
      }
    }
    analogWrite(ANALOG_OUT, smart_map(control, 0, 100, 0, 255));
    sprintf(sprintfStr, "%s %s %s %s", dtostrf(measurement, 5, 1, float1Str), dtostrf(control, 5, 1, float2Str), dtostrf(reference, 5, 1, float3Str), dtostrf(control_i, 5, 1, float4Str));
    Serial.println(sprintfStr);
    flagParams = false;
  }
  // LCD
  if (counterLCD > 10) {
    lcd.setCursor(0, 0);
    sprintf(sprintfStr, "%-8sR=%s%%", (manual ? "MAN" : "AUTO"), dtostrf(reference, 5, 1, float3Str));
    lcd.print(sprintfStr);
    lcd.setCursor(0, 1);
    sprintf(sprintfStr, "U=%s%%Y=%s%%", dtostrf(control, 5, 1, float2Str), dtostrf(measurement, 5, 1, float1Str));
    lcd.print(sprintfStr);
    counterLCD -= 10;
  }
  // Serial
  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case 'P':
        Kp = Serial.parseFloat();
        EEPROM.put(PARAM_ADDR_Kp, Kp);
        break;
      case 'I':
        Ti = Serial.parseFloat();
        EEPROM.put(PARAM_ADDR_Ti, Ti);
        control_i = 0;
        break;
      case 'H':
        SH = Serial.parseFloat();
        EEPROM.put(PARAM_ADDR_SH, SH);
        break;
      case 'L':
        SL = Serial.parseFloat();
        EEPROM.put(PARAM_ADDR_SL, SL);
        break;
      case 'U':
        control = Serial.parseFloat();
        break;
      case 'R':
        reference = Serial.parseFloat();
        break;
      case 'T':
        if (manual) {
          control_i = control;
        }
        manual = !manual;
        updateLED();
        break;
    }
  }
  // Buttons
  unsigned long time = millis();
  for (int i = 0; i < 3; ++i) {
    // Serial.print(digitalRead(BUTTON_PINS[i]));
    // Serial.print(" ");
    if (digitalRead(BUTTON_PINS[i]) == HIGH) {
      if (buttonStates[i] == LOW) {
        // Rising edge
        debounceTimers[i] = time;
      }
      buttonStates[i] = HIGH;
    } else {
      debounceTimers[i] = time;
      buttonStates[i] = LOW;
      repeating[i] = false;
    }
    if (time - debounceTimers[i] > DEBOUNCE_THRESHOLD && !repeating[i]) {
      repeating[i] = true;
      switch (BUTTON_PINS[i]) {
        case BUTTON_LEFT:
          if (manual) {
            control -= 0.5;
          } else {
            reference -= 0.5;
          }
          break;
        case BUTTON_RIGHT:
          if (manual) {
            control += 0.5;
          } else {
            reference += 0.5;
          }
          break;
        case BUTTON_CENTER:
          if (manual) {
            control_i = control;
          }
          manual = !manual;
          updateLED();
          break;
      }
      control = constrain(control, 0, 100);
      reference = constrain(reference, 0, 100);
    }
    if (time - debounceTimers[i] > DEBOUNCE_THRESHOLD + HOLD_THRESHOLD && repeating[i]) {
      debounceTimers[i] += HOLD_REPEAT;
      switch (BUTTON_PINS[i]) {
        case BUTTON_LEFT:
          if (manual) {
            control -= 5;
          } else {
            reference -= 5;
          }
          break;
        case BUTTON_RIGHT:
          if (manual) {
            control += 5;
          } else {
            reference += 5;
          }
          break;
      }
      control = constrain(control, 0, 100);
      reference = constrain(reference, 0, 100);
    }
  }
  // Serial.println();
}

ISR(TIMER1_COMPA_vect) {
  flagParams = true;
  ++counterLCD;
}
