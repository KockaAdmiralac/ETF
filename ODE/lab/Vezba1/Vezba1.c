//BUTTON VCC
//PULLDOWN RA0..3
//LED B
//USB UART
//UART RC6..7

unsigned short state;
short i;
char str[7];

void main() 
{
  ANSELA = 0;
  ANSELC = 0;
  TRISA = 0xF;
  TRISB = 0;
  LATB = 0;
  state = 0;

  UART1_Init(9600);
  Delay_ms(100);

  while (1) 
  {
    for (i = 0; i < 4; i++) 
    {
      if ((state & (1 << i)) == 0 && Button(&PORTA, i, 5, 1)) 
      {
        LATB ^= (1 << i);
        state |= (1 << i);
      }
      if ((state & (1 << i)) != 0 && Button(&PORTA, i, 5, 0))
      {
        state &= ~(1 << i);
      }
    }

    if (UART1_Data_Ready())
    {
      if (UART1_Read() == 'r') 
      {
        IntToStr(LATB, str);
        UART1_Write_Text(Ltrim(str));
        UART1_Write(13);
        UART1_Write(10);
      }
    }
  }
}