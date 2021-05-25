//7SEG RA0..3

unsigned short numberIndex, changeNumberFlag, disp, i, swapdigit;
int tick;
int niz[] = { 1234, 9876, 537,6329 ,7948};
unsigned short masks[4];

unsigned short mask(unsigned short num) 
{
  switch (num) 
  {
    case 0 : return 0x3F;
    case 1 : return 0x06;
    case 2 : return 0x5B;
    case 3 : return 0x4F;
    case 4 : return 0x66;
    case 5 : return 0x6D;
    case 6 : return 0x7D;
    case 7 : return 0x07;
    case 8 : return 0x7F;
    case 9 : return 0x6F;
  }
}

unsigned short getDigit(int number, unsigned short digit) 
{
  switch (digit) 
  {
    case 0: return number % 10;
    case 1: return (number / 10) % 10;
    case 2: return (number / 100) % 10;
    case 3: return (number / 1000) % 10;
  }
}

// Period: 1000/(2*10^6)=0.5ms
// Korekcija za overhead izvrsavanja prekidne rutine 988
void interrupt() 
{
  TMR0H = 0xFC;
  TMR0L = 0x24;
  //TMR0L = 0x18;

  LATA = 0;
  LATD = masks[disp];
  LATA = (1 << disp);
  disp = (disp + 1) % 4;

  //if (tick < 10000)
  if (tick < 9800)  // Korekcija za overhead promene broja 9800
  {
    tick++;
  }
  else 
  {
    tick = 0;
    changeNumberFlag = 1;
  }

  TMR0IF_bit = 0;
}

void main() 
{
  ANSELA = 0;
  ANSELD = 0;
  TRISA = 0;
  TRISD = 0;
  LATA = 0;
  LATD = 0;
  TMR0H = 0xFC;
  TMR0L = 0x24;
  T0CON = 0x88;
  //TMR0L = 0x18;
  
  numberIndex = 0;
  changeNumberFlag = 0;
  disp = 0;
  tick = 0;
  swapdigit=0;
  
  for(i=0;i<4;i++)
  {
    masks[i]=mask(getDigit(niz[numberIndex], i));
  }

  GIE_bit = 1; // Enable all unmasked interrupts
  TMR0IE_bit = 1; // Enable TMR0 overflow interrupt

  while(1) 
  {
    if (changeNumberFlag) 
    {
      numberIndex=(numberIndex+1)%(sizeof(niz)/sizeof(int));
      for(i=0;i<4;i++)
      {
        masks[i]=mask(getDigit(niz[numberIndex], i));
      }
      changeNumberFlag = 0;
    }
  }
}