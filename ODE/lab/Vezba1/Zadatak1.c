// NOTES:
// - Turn ON the PORTA LEDs at SW3.1 and PORTD LEDs at SW3.4.
// - Put button jumper (J17) into VCC position.
// - Pull-down RB0.
// - Put jumpers J3 and J4 into USB UART position.
// - Turn ON RX and TX USB UART switches (SW1.1 and SW2.1).

char uart_rd;

void main() 
{
  ANSELB = 0; // Configure PORTB pins as digital
  ANSELC = 0; // Configure PORTC pins as digital

  TRISA = 0; // set direction to be output
  TRISB = 0x01; // set RB0 pin as input
  TRISD = 0; // set direction to be output

  LATA = 0x00; // Turn OFF LEDs on PORTA
  LATD = 0x00; // Turn OFF LEDs on PORTD

  UART1_Init(9600); // Initialize UART module at 9600 bps
  Delay_ms(100); // Wait for UART module to stabilize

  UART1_Write_Text("Start");
  UART1_Write(13);
  UART1_Write(10);

  while (1)
  {
    if (Button(&PORTB, 0, 5, 1)) // Detect logical one
    {
      LATA = 0x03; // Turn ON two LEDs (RA0 and RA1) on PORTA
      LATD = 0x03; // Turn ON two LEDs (RD0 and RD1) on PORTD
    }
    if (Button(&PORTB, 0, 5, 0)) // Detect logical zero
    {
      LATA = 0x00; // Turn OFF LEDs on PORTA
      LATD = 0x00; // Turn OFF LEDs on PORTD
    }
    if (UART1_Data_Ready())
    { // If data is received,
      uart_rd = UART1_Read(); // read the received data,
      UART1_Write(uart_rd); // and send data via UART
    }
  }
}