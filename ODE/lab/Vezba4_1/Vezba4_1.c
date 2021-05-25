//BUTTON VCC
//PULLDOWN RD0..3
//REMOVE X1
//RA6..7 IO

short tick;

void main() 
{
  OSCCON =  0b00100011; //500 INTOSC
  OSCCON2 = 0b00000000; //HF
  OSCTUNE = 0b01000000; //LF31.25 PLL

  TRISA = 0x00;
  LATA = 0x00;
  ANSELD = 0x00;
  TRISD = 0x0F;
  
  tick = 0;
  
  while (1)
  {
    if (PORTD & 0b0001) // HF 500
    {
      OSCCON = 0b00100011; // 500
      OSCCON2 = 0b00000000; //HF
    }
    if (PORTD & 0b0010) // MF 250
    {
      OSCCON = 0b00010011; // 250
      OSCCON2 = 0b00010000; //MF
    }
    if (PORTD & 0b0100) // LF 31.25
    {
      OSCCON = 0b00000011; // 31.25
    }
    if (PORTD & 0b1000) // HF 4M x4 PLL
    {
      OSCCON = 0b01010000; //4M
      OSCCON2 = 0b00000000; //HF
    }

    if (tick == 10) 
    {
      LATA ^= 0x80;
    }
    if (tick == 20) 
    {
      LATA ^= 0xC0;
      tick = 0;
    }
    tick++;
  }
}