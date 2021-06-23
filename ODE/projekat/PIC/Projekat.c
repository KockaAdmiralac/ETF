//LCD
//PWM BACKLIGHT
//P1 RA1
//RD1 PWM

sbit LCD_RS at LATB4_bit;
sbit LCD_EN at LATB5_bit;
sbit LCD_D4 at LATB0_bit;
sbit LCD_D5 at LATB1_bit;
sbit LCD_D6 at LATB2_bit;
sbit LCD_D7 at LATB3_bit;
sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

int currADCValue;
int oldADCValue;
char str[6];
int tmp;
char msg[5];
unsigned char uartBit;
int period;

void interrupt()
{
  currADCValue = ADRESH<<2 | (ADRESL >> 6);

  ADIF_bit = 0;
  ADCON0 |= 0x02; // Start A/D conversion
}


void main()
{
  ANSELA = 0x02;
  TRISA = 0x02;
  ANSELB = 0;
  ANSELC = 0;
  ANSELD = 0x00;
  TRISD = 0x00;

  CCP4CON = 0b00001100; // Two LSBs of the PWM duty cycle: 00; PWM mode
  CCPR4L = 0;           // Eight MSBs of the PWM duty cycle
  PR4 = 24;             // PWM period value
  CCPTMRS1 = 0x01;      // CCP4 PWM modes use Timer4
  T4CON = 0b0000100;    // Enable the Timer4; Prescaler is 1

  ADCON0 = 0b00000101;  // Select analog channel AN1 AD conversion not in progress; ACD is enabled
  ADCON1 = 0b00000000;  // Positive voltage reference connected to AVDD Negative voltage reference connected to AVSS
  ADCON2 = 0b00010100;  // A/D conversion result left justified A/D acquisition time 4Tad A/D conversion clock Fosc/4 = 2MHz

  ADIF_bit = 0;
  GIE_bit = 1;
  PEIE_bit = 1;
  ADIE_bit = 1;

  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  UART1_Init(9600);
  Delay_ms(100);

  uartBit = 0;
  str[5] = '\0';
  str[4] = 'V';
  str[1] = '.';
  currADCValue = 0;
  oldADCValue = 1;
  ADCON0 |= 0x02;

  while (1)
  {
    if (UART1_Data_Ready())
    {
      msg[uartBit++] = UART1_Read();
      if (msg[uartBit-1] == '\0') {
        if (uartBit == 5) {
          //period = (msg[0] - '0' + (msg[2] - '0') * 0.1 + (msg[3] - '0') * 0.01)*20;
          period= ((msg[0] - '0')*100 + (msg[2] - '0') * 10 + (msg[3] - '0'))*0.2;
          CCPR4L = period >> 2;
          CCP4CON = ((period & 3) << 4) | 0b1100;
        }
        uartBit = 0;
      }
    }
    if (currADCValue - oldADCValue > 2 || currADCValue - oldADCValue < -2)
    {
      oldADCValue = currADCValue;
      tmp = oldADCValue * 5 / 10.23;
      str[0] = (tmp / 100) + '0';
      str[2] = ((tmp / 10) % 10) + '0';
      str[3] = (tmp % 10) + '0';
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1, 7, str);
      UART1_Write_Text(str);
      Delay_ms(30);
    }
  }
}