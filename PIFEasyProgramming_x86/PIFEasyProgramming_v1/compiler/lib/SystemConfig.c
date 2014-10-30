/*
 * SystemConfig.c
 *
 *  Created on: Aug 13, 2014
 *      Author: HUAN
 */
#include <msp430g2553.h>
#include "SPI.h"
void ConfigADC(void)
{
	ADC10CTL1 = INCH_4 + CONSEQ_1;            // A3->A0, multi channel
	ADC10CTL0 = REFON + REF2_5V + ADC10SHT_2 + MSC + ADC10ON;
	ADC10AE0 = 0x11;                          // P1.0,P1.3,P1.4 ADC option select
	ADC10DTC1 = 0x05;                         // 5 conversions                        // 3 conversions
}
void ConfigTimer(int time)
{
	TA0CTL |= TASSEL_2 + MC_1 + ID_0 + TAIE; // Start timerA0 in up mode , SMCLK
	TA0CCR0 = time * 1000;							//Frequency:
}
void ConfigBuzzer()
{
	P2DIR |= BIT2;
	P2SEL |= BIT2;
	P2SEL2 &= ~BIT2;
	
	TA1CTL |= TASSEL_2 + MC_1 + ID_0 ; // Start timerA1 in up mode , SMCLK
	TA1CCR0 = 500;							//Frequency: 2KHz
	TA1CCTL1 = OUTMOD_7;
	TA1CCR1 = 0;							//Turn off buzzer
}
void ConfigButton(void)
{
	P2DIR &= ~(BIT3 + BIT4);
	P2REN |= BIT3 + BIT4;
	P2OUT |= BIT3 + BIT4;
	
	__delay_cycles(100000);
//	P2IE |= BIT3;
//	P2IES |= BIT3;
//	P2IFG &= ~BIT3;
}
void ConfigIndicator(void)
{
	int i;
	P1SEL &= ~BIT6;
	P1SEL2 &= ~BIT6;
	P1DIR |= BIT6;
	P1OUT &= ~BIT6;
	for (i = 0; i < 20; i++)
	{
		P1OUT ^= BIT6;
		__delay_cycles(100000);
	}
}
void ConfigMotor()
{
		// Setup SCL, SDA pins as I/O function
	PinTypeDigital(SCL_PORT, SCL_PIN);
	PinTypeDigital(SDA_PORT, SDA_PIN);
	PinTypeDigital(CS_PORT, CS_PIN);
  	// Setup SCL, SDA pins as output
	PinTypeOutput(SCL_PORT, SCL_PIN);
	PinTypeOutput(SDA_PORT, SDA_PIN);
	PinTypeOutput(CS_PORT, CS_PIN);
	// Reset SCL, SDA pin to Low
	PinSet(SCL_PORT, SCL_PIN);
	PinSet(SDA_PORT, SDA_PIN);
	PinSet(CS_PORT, CS_PIN);
}
void ConfigLed()
{
	P2SEL &= ~(BIT0 + BIT1);
	P2SEL2 &= ~(BIT0 + BIT1);
	P2DIR |= (BIT0 + BIT1);
	P2OUT &= ~(BIT0 + BIT1);
}
