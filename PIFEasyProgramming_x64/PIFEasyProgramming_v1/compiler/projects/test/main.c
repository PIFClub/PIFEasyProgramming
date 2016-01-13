#include <msp430g2553.h>
#include <stdbool.h>
#include "SystemConfig.h"
#include "System.h"
#include "SPI.h"
int right;
int value[5];
int left;
int base[5];
void config1();
void config1()
{
	ConfigADC();
	ConfigMotor();
	ConfigLed();
	ConfigBuzzer();
	ConfigButton();
	ConfigTimer(10);
}
void main()
{
	WDTCTL = WDTHOLD | WDTPW;
	config1();
	WaitButton(true);
	StartSamples(base);
	while(!(ADC10CTL0 & ADC10IFG));
	ADC10CTL0 &= ~ADC10IFG;
	WaitButton(true);
	__enable_interrupt();
	while(1)
	{
		while(!(ADC10CTL0 & ADC10IFG));
		ADC10CTL0 &= ~ADC10IFG;
		PID(base,value,0.6,0.05,0.0,45,&left,&right);
		SetPWM(left,right);
	}
}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerIntHandler1()
{
if (TA0IV == 0x0A)
{
	StartSamples(value);
}
}
