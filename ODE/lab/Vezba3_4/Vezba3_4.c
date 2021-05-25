//LCD
//PWM BACKLIGHT
//P1 RA3
//5V

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

unsigned int currADCValue;
unsigned int oldADCValue;
char str[17];
float tmp;

void interrupt() 
{
  currADCValue = (ADRESH << 8) | ADRESL;

  ADIF_bit = 0;
  ADCON0 |= 0x02; // Start A/D conversion
}

void main() 
{
  TRISA = 0x08;
  ANSELA = 0x08;
  ANSELB = 0;

  ADCON0 = 0b00001101;          // Select analog channel AN3;
                                // AD conversion not in progress; ACD is enabled
  ADCON1 = 0b00001000;          // Positive voltage reference connected to FVR BUF2;
                                // Negative voltage reference connected to AVSS
  ADCON2 = 0b10011001;          // A/D conversion result right justified;
                                // A/D acquisition time 6Tad;
                                // A/D conversion clock Fosc/8 = 1MHz
  VREFCON0 = 0b10110000;        // FVR enabled; 4x output
  while ((VREFCON0 & 0x40)==0){}  // Wait for FVR to stabilize

  ADIF_bit = 0;
  GIE_bit = 1;
  PEIE_bit = 1;
  ADIE_bit = 1;

  oldADCValue = 1;
  currADCValue = 0;

  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  
  ADCON0 |= 0x02; // Start A/D conversion

  while (1) 
  {
    if (currADCValue - oldADCValue > 2 || currADCValue - oldADCValue < -2) 
    {
      oldADCValue = currADCValue;
      tmp = currADCValue * 4.096 / 1023.0;
      FloatToStr(tmp, str);
      Lcd_Cmd(_LCD_CLEAR);
      Lcd_Out(1, 4, str);
    }
    Delay_ms(30);
  }
}