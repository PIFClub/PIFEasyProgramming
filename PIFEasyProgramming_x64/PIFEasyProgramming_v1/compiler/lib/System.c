/*
 * System.c
 *
 *  Created on: Aug 15, 2014
 *      Author: HUAN
 */
#include <stdint.h>
#include <stdbool.h>
#include <msp430g2553.h>
/**
 * Light sensor
 */
void StartSamples(int *ADCresult)
{
    ADC10CTL0 &= ~ENC;
    while (ADC10CTL1 & BUSY);
    ADC10SA = (unsigned int)ADCresult;
    ADC10CTL0 |= ENC + ADC10SC;
}
/**
 * Button
 */
void WaitButton(bool isLeft)
{
	if (isLeft)
	{	
		while (P2IN & BIT4);
		__delay_cycles(100000);
		while (!(P2IN & BIT4));
		__delay_cycles(100000);
	}
	else
	{
		while (P2IN & BIT3);
		__delay_cycles(100000);
		while (!(P2IN & BIT3));
		__delay_cycles(100000);
	}
}
/**
 * Motor
 */
void PID(int *base, int *value, double Kp, double Ki, double Kd, int avgSpeed,int *left, int *right)
{
	static double pPart=0, iPart=0, dPart=0, pidResult=0;
	static int pre_error=0, prepre_error=0;
	int error;
	int Delta[5], i;
	for (i = 0; i < 5; i++)
	{
		Delta[i] = base[i] - value[i];
	}
	error=Delta[0] - Delta[4];

	pPart = (Kp+Ki+Kd) * error;
	iPart = -(Kp+2*Kd) * pre_error;
	dPart = Ki * prepre_error;
	pidResult += pPart + iPart + dPart;

	if (pidResult > 80)
		pidResult = 80;
	if (pidResult < -80)
		pidResult = -80;

	pre_error = error;
	prepre_error = pre_error;

	*left = avgSpeed+ pidResult/2;
	*right = avgSpeed- pidResult/2;

	if (*left > 90)
		*left = 90;
	else if (*left <-90)
		*left = -90;
	if (*right > 90)
		*right = 90;
	else if (*right <-90)
		*right = -90;
}
/**
 * Time
 */
void delay_ms(int ms)
{
	int i;
	for (i=0;i<ms;i++)
	{
		__delay_cycles(1000);
	}
}
/**
 * Led
 */
void ToggleLed(bool isLeft)
{
	if (isLeft)
		P2OUT ^= BIT1;
	else
		P2OUT ^= BIT0;
}
void TurnOnLed(bool isLeft)
{
	if (isLeft)
		P2OUT |= BIT1;
	else
		P2OUT |= BIT0;
}
void TurnOffLed(bool isLeft)
{
	if (isLeft)
		P2OUT &= ~BIT1;
	else
		P2OUT &= ~BIT0;
}
/**
*	Buzzer	
**/
void TurnOnBuzzer()
{
	TA1CCR1 = 250;
}
void TurnOffBuzzer()
{
	TA1CCR1 = 0;
}
