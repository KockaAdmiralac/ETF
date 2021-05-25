//BUTTON VCC
//PULLDOWN RA0..3
//LED B

unsigned short state;
short i;

void main() 
{
  ANSELA = 0;
  TRISA = 0xF;
  TRISB = 0;
  LATB = 0;
  state = 0;

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
  }
}