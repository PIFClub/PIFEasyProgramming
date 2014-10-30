#include "SPI.h"

volatile unsigned char RxData = 0;

void Config_SPI_Master_A(void) // Config module SPI USCIA
{
	//Config PIN
	P1SEL |= BIT1 + BIT2 + BIT4 + BIT5;
	P1SEL2 |= BIT1 + BIT2 + BIT4 + BIT5;
	//Config SPI
	UCA0CTL0 |= UCCKPL + UCMSB + UCSYNC + UCMST + UCMODE_1;
		/*	UCSYNC     Sync-Mode
		 *  UCCKPH     Mode: Clock Phase
		 *	UCCKPL     Mode: Clock Polarity
		 *	UCMST      Mode: Master Select
		 *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
		 *  UCMSB	   Mode: MSB first  0:LSB / 1:MSB
		 *	UCMST      Mode: Master Select
		 *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
		 *	UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
		 *	UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
		 */
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
		/*UCSSEL_1 ACLK
		 *UCSSEL_2 SMCLK
		 *UCSSEL_3 SMCLK
		 */
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	UCA0BR0 |= 0x02;                          // f/2    for your choice
	UCA0BR1 = 0;                              //

	UCA0MCTL = 0;                             // No modulation

//	IE2 |= UCA0TXIE;                          // Enable USCI0 RX interrupt
	__delay_cycles(75);                       // Wait for slave to initialize
}


void Config_SPI_Master_B(void) // Config module SPI USCIB
{
	//Config PIN
	P1SEL |= BIT4 + BIT5 + BIT6 + BIT7;
	P1SEL2 |= BIT4 + BIT5 + BIT6 + BIT7;
	//Config SPI
	UCB0CTL0 |= UCCKPL + UCMSB + UCSYNC + UCMST + UCMODE_0;
	/*	UCSYNC     Sync-Mode
	 *  UCCKPH     Mode: Clock Phase
	 *	UCCKPL     Mode: Clock Polarity
	 *	UCMST      Mode: Master Select
	 *  UC7BIT     Mode: Data Bits  0:8-bits / 1:7-bits
	 *  UCMSB	   Mode: MSB first  0:LSB / 1:MSB
	 *	UCMST      Mode: Master Select
	 *  UCMODE_0   Mode: USCI Mode: 0; 3pin SPI default
	 *	UCMODE_1    Mode: USCI Mode: 1; 4pin SPI
	 *	UCMODE_2    Mode: USCI Mode: 2; 4pin SPI
	 */
	UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	/*UCSSEL_1 ACLK
	 *UCSSEL_2 SMCLK
	 *UCSSEL_3 SMCLK
	 */
	UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**

	UCB0BR0 |= 0x0a;                         // f/2   for your choice
	UCB0BR1 = 0;                              
//	IE2 |= UCB0RXIE;                         // Enable USCI0 RX interrupt
	__delay_cycles(75);                      // Wait for slave to initialize
}


void Send_byte_A(int data, int time_ms)     // Send 1 byte for module SPI USCIA
{
	  int i_delay;
	  while (!(IFG2 & UCA0TXIFG));          // USCI_A0 TX buffer ready?
	  UCA0TXBUF = data;                     // Send next value
	  for (i_delay = 0; i_delay<time_ms; i_delay++ )
	  {
		__delay_cycles(1000);
	  }
}

void Send_byte_B(int data, int time_ms)     // Send 1 byte for module SPI USCIB
{
	  int i_delay;
	  while (!(IFG2 & UCB0TXIFG));          // USCI_A0 TX buffer ready?
	  UCB0TXBUF = data;                     // Send next value
	  for (i_delay = 0; i_delay<time_ms; i_delay++ )
	  {
		__delay_cycles(1000);
	  }
}

void Send_byte_SW(char d)
{
	unsigned char bit;

	PinReset(CS_PORT, CS_PIN);
    for(bit = 0x80; bit; bit >>= 1) {
    	PinReset(SCL_PORT, SCL_PIN);
      if(d & bit) PinSet(SDA_PORT, SDA_PIN);
      else        PinReset(SDA_PORT, SDA_PIN);
      __delay_cycles(10);
      PinSet(SCL_PORT, SCL_PIN);
      __delay_cycles(5);
    }
	PinSet(CS_PORT, CS_PIN);
}

void SetPWM(char duty_left, char duty_right)
{
	Send_byte_SW(duty_left);
	__delay_cycles(100);
	Send_byte_SW(duty_right);
	__delay_cycles(100);
	Send_byte_SW(0x7f);
	__delay_cycles(100);
}
//GCC toolchain

