/*
 * test.c
 *
 *  Created on: Mar 26, 2023
 *      Author: egr
 */


#include <hw_types.h>
#include"EGR_DCMotor.h"
#include"Conf_mod.h"
#include"EGR_Cape.h"
#include"GPIO.h"
#include"delay_ms.h"

int main(){


	//initailise motor
	EHRPWMinitForDCMotor();

	// mux motor pin
	PinMuxing(CONF_H_BRUECKE_MOTOR1_1,PULL_DISABLE,0,6);
	PinMuxing(CONF_H_BRUECKE_MOTOR1_2,PULL_DISABLE,0,6);

	PinMuxing(CONF_H_BRUECKE_MOTOR2_1,PULL_DISABLE,0,4);
	PinMuxing(CONF_H_BRUECKE_MOTOR2_2,PULL_DISABLE,0,4);

	//set input
	PinMuxing(CONF_PORT1_PIN2,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p2, as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input

	unsigned int last_state = 1;

	// max
	EHRPWMsetDutyCycle(SOC_EPWM_1_REGS,100);
	EHRPWMsetDutyCycle(SOC_EPWM_2_REGS,100);

	while(1){

		if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW){
			last_state = !last_state;
//			speed = speed - 20;
			delay_ms(250); // xiaochu anjian doudong
			}else{}

		if(last_state){
			configEHRPWM_A(SOC_EPWM_1_REGS,EHRPWM_SET_OUTPUT_HIGH,EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_1_REGS,EHRPWM_SET_OUTPUT_LOW,EHRPWM_SET_OUTPUT_LOW);//left wheel

			configEHRPWM_A(SOC_EPWM_2_REGS,EHRPWM_SET_OUTPUT_LOW,EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_2_REGS,EHRPWM_SET_OUTPUT_HIGH,EHRPWM_SET_OUTPUT_LOW);//right wheel
			//forward
		}else{
			configEHRPWM_A(SOC_EPWM_1_REGS,EHRPWM_SET_OUTPUT_LOW,EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_1_REGS,EHRPWM_SET_OUTPUT_HIGH,EHRPWM_SET_OUTPUT_LOW);

			configEHRPWM_A(SOC_EPWM_2_REGS,EHRPWM_SET_OUTPUT_HIGH,EHRPWM_SET_OUTPUT_LOW);
			configEHRPWM_B(SOC_EPWM_2_REGS,EHRPWM_SET_OUTPUT_LOW,EHRPWM_SET_OUTPUT_LOW);
			// reverse
		}



	}
	return 0;
}
