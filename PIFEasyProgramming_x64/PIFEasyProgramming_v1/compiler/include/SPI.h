#ifndef SPI_H_
#define SPI_H_

#include <msp430g2553.h>

#define SCL_PORT		1
#define SDA_PORT		1
#define CS_PORT			2

#define CS_PIN			BIT5
#define SCL_PIN			BIT5
#define SDA_PIN			BIT7

#define PinTypeDigital(PORTNUM, PIN)				GPIOPinTypeDigital(PORTNUM, PIN)
#define GPIOPinTypeDigital(PORTNUM, PIN)			{ 	P##PORTNUM##SEL &= ~PIN;	\
														P##PORTNUM##SEL2 &= ~PIN;}
#define PinTypePrimaryFuntion(PORTNUM, PIN)			GPIOPinTypePrimaryFuntion(PORTNUM, PIN)
#define GPIOPinTypePrimaryFuntion(PORTNUM, PIN)		{ 	P##PORTNUM##SEL |= PIN;		\
														P##PORTNUM##SEL2 &= ~PIN;}
#define PinTypeSecondaryFunction(PORTNUM, PIN)		GPIOPinTypeSecondaryFunction(PORTNUM, PIN)
#define GPIOPinTypeSecondaryFunction(PORTNUM, PIN)	{ 	P##PORTNUM##SEL |= PIN;		\
														P##PORTNUM##SEL2 |= PIN;}

#define PinTypeOutput(PORTNUM, PIN)					GPIOPinTypeOutput(PORTNUM, PIN)
#define GPIOPinTypeOutput(PORTNUM, PIN)				(	P##PORTNUM##DIR |= PIN)

#define PinTypeInput(PORTNUM, PIN)					GPIOPinTypeInput(PORTNUM, PIN)
#define GPIOPinTypeInput(PORTNUM, PIN)				(	P##PORTNUM##DIR &= ~PIN)

#define PinSet(PORTNUM, PIN)						GPIOPinSet(PORTNUM, PIN)
#define GPIOPinSet(PORTNUM, PIN)					(	P##PORTNUM##OUT |= PIN)

#define PinReset(PORTNUM, PIN)						GPIOPinReset(PORTNUM, PIN)
#define GPIOPinReset(PORTNUM, PIN)					(	P##PORTNUM##OUT &= ~PIN)

void Config_SPI_Master_A(void);
void Config_SPI_Master_B(void);
void Send_byte_A(int data, int time_ms);
void Send_byte_B(int data, int time_ms);
void SetPWM(char duty_left, char duty_right);

#endif /* SPI_H_ */

