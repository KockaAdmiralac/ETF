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

//Freq:40kHz Period:25us
//PR4=(25*10^-6 * 8*10^6 / 4)-1=50-1=49
//DCR 10%,30%,50%,70%,90% (0.5,1.5,2.5,3.5,4.5)V
//CCPR4=DCR*4*(49+1)=DCR*200
//CCPR4=20,60,100,140,180

unsigned short DCRs[] = {20,60,100,140,180};
unsigned short DCRindex=0;
unsigned short freq=1;
unsigned short tick=0;
char str[7];

void main() 
{
  ANSELB = 0;
  ANSELD = 0x00;
  TRISD = 0x00;
  
  CCP4CON = 0b00001100; // Two LSBs of the PWM duty cycle: 11; PWM mode
  CCPR4L = 5;           // Eight MSBs of the PWM duty cycle
  PR4 = 49;             // PWM period value
  CCPTMRS1 = 0x01;      // CCP4 PWM modes use Timer4
  T4CON = 0b0000100;    // Enable the Timer4; Prescaler is 1
  
  Lcd_Init();
  Lcd_Cmd(_LCD_CURSOR_OFF);
  
  while (1) 
  {
    if(tick==5)
    {
      DCRindex=(DCRindex+1)%(sizeof(DCRs)/sizeof(unsigned short));
      CCP4CON = 0b00001100|((DCRs[DCRindex]&0x03)<<4);
      CCPR4L = DCRs[DCRindex]>>2;
      tick=0;
    }

    Lcd_Cmd(_LCD_CLEAR);
    if(freq)
    {
      Lcd_Out(1, 1, "Frequency:");
      Lcd_Out(2, 6, "40kHz");
      freq=0;
    }
    else
    {
      IntToStr(DCRs[DCRindex]/2, str);
      Lcd_Out(1, 1, "Duty Cycle Rate:");
      Lcd_Out(2, 6, Ltrim(str));
      Lcd_Out(2, 8, "%");
      freq=1;
    }
    tick++;
    Delay_ms(2000);
  }
}