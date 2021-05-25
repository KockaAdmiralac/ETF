//LCD
//PWM BACKLIGHT
//INSERT X1
//RA6..7 OSC

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

//Freq:80kHz Period:12.5us
//PR4=(12.5*10^-6 * 8*10^6 / 4)-1=25-1=24
//DCR 66.67%
//CCPR4=0.6667*4*(24+1)=66.67~~67
//CCPR4=0b01000011

void main() 
{
  ANSELB = 0;
  ANSELD = 0x00;
  TRISD = 0x00;
  
  CCP4CON = 0b00111100; // Two LSBs of the PWM duty cycle: 11; PWM mode
  CCPR4L = 16;          // Eight MSBs of the PWM duty cycle
  PR4 = 24;             // PWM period value
  CCPTMRS1 = 0x01;      // CCP4 PWM modes use Timer4
  T4CON = 0b0000100;    // Enable the Timer4; Prescaler is 1
  
  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  
  while (1) 
  {
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "Frequency:");
    Lcd_Out(2, 6, "80kHz");
    Delay_ms(2000);
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Out(1, 1, "Duty Cycle Rate:");
    Lcd_Out(2, 6, "30%");
    Delay_ms(2000);
  }
}