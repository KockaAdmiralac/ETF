//LCD
//PWM BACKLIGHT 

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

char txt1[] = "mikroElektronika";
char txt2[] = "EasyPIC7";
char txt3[] = "Lcd4bit";
char txt4[] = "example";
char i;

void main()
{
  ANSELB = 0;
  
  Lcd_Init();
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Cmd(_LCD_CURSOR_OFF);
  Lcd_Out(1, 6, txt3);
  Lcd_Out(2, 6, txt4);
  Delay_ms(2000);
  
  Lcd_Cmd(_LCD_CLEAR);
  Lcd_Out(1, 1, txt1);
  Lcd_Out(2, 5, txt2);
  Delay_ms(2000);
  
  for(i = 0; i < 4; i++) 
  {
    Lcd_Cmd(_LCD_SHIFT_RIGHT);
    Delay_ms(500);
  }
  while(1) 
  {
    for(i = 0; i < 8; i++) 
    {
      Lcd_Cmd(_LCD_SHIFT_LEFT);
      Delay_ms(500);
    }
    for(i = 0; i < 8; i++) 
    {
      Lcd_Cmd(_LCD_SHIFT_RIGHT);
      Delay_ms(500);
    }
  }
}