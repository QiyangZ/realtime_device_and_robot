/* EGR */
/*============Aufgabe 1 UND Aufgabe 2============================================*/
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
	int speed = 77;

	PinMuxing(CONF_PORT1_PIN2,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p2, as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input
	while(1){
		if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW){delay_ms(5000); break;}

	}

	while(1){
		MotorSpeedSet (speed);
		signal[0] = get_IR_data();
		unsigned int bottom_left = signal[0] & 0b01000000 ? 1 : 0;
		unsigned int bottom_mitl = signal[0] & 0b00100000 ? 1 : 0;
		unsigned int bottom_rigt = signal[0] & 0b00010000 ? 1 : 0;
		unsigned int frontt_left = signal[0] & 0b00001000 ? 1 : 0;
		unsigned int frontt_mitl = signal[0] & 0b00000100 ? 1 : 0;
		unsigned int frontt_rigt = signal[0] & 0b00000010 ? 1 : 0;
		UARTprintf(" Bottom: %d %d %d \t Front:%d %d %d \n",bottom_left,bottom_mitl,bottom_rigt,frontt_left,frontt_mitl,frontt_rigt);

		if( bottom_rigt==0 ){MotorRechts(speed);}
		if(bottom_left==1){MotorLinks(speed);}
//		if(bottom_left==1 && bottom_mitl==1 && bottom_rigt==0){MotorLinks(speed);}
//		if(bottom_left==1 && bottom_mitl==0 && bottom_rigt==0){MotorRechts(speed);}
		if(bottom_left==0 && bottom_mitl==1 && bottom_rigt==0){MotorRechts(speed); MotorRechts(speed);}
		if(bottom_left==1 && bottom_mitl==1 && bottom_rigt==0){MotorRechts(speed);delay_ms(500); MotorRechts(speed);delay(100);}//baisexoaoquan
		if(bottom_left==0 && bottom_mitl==0 && bottom_rigt==1){LinkRad_RehctsRad(speed,0);}
		if(bottom_left==0 && bottom_mitl==0 && bottom_rigt==0){LinkRad_RehctsRad(0,0);delay_ms(100); LinkRad_RehctsRad(speed,0);}
//		if(bottom_left==1 && bottom_rigt==1){MotorLinks(speed);}
		delay_ms(30);
	}
}
