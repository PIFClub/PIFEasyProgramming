#include <msp430g2553.h>
#include <stdbool.h>
#include "SystemConfig.h"
#include "System.h"
#include "SPI.h"
void config1();
void config1()
{
	ConfigADC();
	ConfigMotor();
	ConfigLed();
	ConfigBuzzer();
	ConfigButton();
}
void main()
{
	WDTCTL = WDTHOLD | WDTPW;
	config1();
	TurnOnLed(true);
	TurnOnBuzzer();
	delay_ms(3000);
	TurnOffBuzzer();
	SetPWM(40,80);
	while(1)
	{
		delay_ms(10);
	}
}
