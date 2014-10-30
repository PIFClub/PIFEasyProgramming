/*
 * System.h
 *
 *  Created on: Aug 15, 2014
 *      Author: HUAN
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_
void StartSamples(int *ADCResult);
void WaitButton(bool isLeft);
void PID(int *base, int *value, double Kp, double Ki, double Kd, int avgSpeed, int *left, int *right);
void sendPWM();
void TurnOnLed(bool isLeft);
void TurnOffLed(bool isLeft);
void ToggleLed(bool isLeft);
void TurnOnBuzzer();
void TurnOffBuzzer();
void delay_ms(int ms);
#endif /* SYSTEM_H_ */
