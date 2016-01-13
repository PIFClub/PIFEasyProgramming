#include <msp430g2553.h>
#include <stdbool.h>
#include "SystemConfig.h"
#include "System.h"
#include "SPI.h"
int Value[5];
int Right;
int Left;
int Base[5];
void beep();
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
void beep()
{
	TurnOnBuzzer();
	delay_ms(1000);
	TurnOffBuzzer();
}
void main()
{
	WDTCTL = WDTHOLD | WDTPW;
	config1();
	WaitButton(true);
	beep();
	StartSamples(Base);
	while(!(ADC10CTL0 & ADC10IFG));
	ADC10CTL0 &= ~ADC10IFG;
	WaitButton(true);
	beep();
	__enable_interrupt();
	while(1)
	{
		while(!(ADC10CTL0 & ADC10IFG));
		ADC10CTL0 &= ~ADC10IFG;
		PID(Base,Value,1.2,0.01,0.0,40,&Left,&Right);
		SetPWM(Left,Right);
	}
}
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TimerIntHandler1()
{
if (TA0IV == 0x0A)
{
	StartSamples(Value);
}
}
