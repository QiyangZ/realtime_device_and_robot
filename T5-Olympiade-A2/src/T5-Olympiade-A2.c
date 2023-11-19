/* EGR */

/***  ===========nicht praktikumsrelevant=========================

#include <hw_types.h>
#include"Motorsteuerung.h"
#include <hw_types.h>
#include "i2c.h"
#include "delay_ms.h"
#include <uartStdio.h>

int main(){

	EHRPWMinitForDCMotor();
	MotorInit_and_Mux (); // everything initialise

	IR_initialise();
	char signal[1] = {};
	int speed = 80;

	while(1){
		MotorSpeedSet (speed);
		signal[0] = get_IR_data();
		unsigned int bottom_left = signal[0] & 0b01000000 ? 1 : 0;
		unsigned int bottom_mitl = signal[0] & 0b00100000 ? 1 : 0;
		unsigned int bottom_rigt = signal[0] & 0b00010000 ? 1 : 0;
//		unsigned int frontt_left = signal[0] & 0b00001000 ? 1 : 0;
//		unsigned int frontt_mitl = signal[0] & 0b00000100 ? 1 : 0;
//		unsigned int frontt_rigt = signal[0] & 0b00000010 ? 1 : 0;
//		UARTprintf(" Bottom: %d %d %d \t Front:%d %d %d \n",bottom_left,bottom_mitl,bottom_rigt,frontt_left,frontt_mitl,frontt_rigt);


		if(bottom_left==0 && bottom_mitl==1 && bottom_rigt==1){MotorSpeedSet (speed);} //hbb

		if(bottom_left==0 && bottom_mitl==0 && bottom_rigt==0){MotorLinks(speed);} // hhh quanhei, butaikeneng
		if(bottom_left==0 && bottom_mitl==0 && bottom_rigt==1){LinkRad_RehctsRad(speed-5,speed+10);} //hhb
//		if(bottom_left==0 && bottom_mitl==1 && bottom_rigt==0){LinkRad_RehctsRad(speed+10,speed-10);} //hbh butaikengn
		if(bottom_left==0 && bottom_mitl==1 && bottom_rigt==1){} //hbb
		if(bottom_left==1 && bottom_mitl==0 && bottom_rigt==0){MotorLinks(speed);} //bhh zaiwaiquan
		if(bottom_left==1 && bottom_mitl==0 && bottom_rigt==1){MotorRechts(speed);} // bhb zaihenwaiquan
		if(bottom_left==1 && bottom_mitl==1 && bottom_rigt==1){MotorLinks(speed);} // bbb quanbai ,shaowei wangyou
		delay_ms(30);
	}

	return 0;
}

***/


