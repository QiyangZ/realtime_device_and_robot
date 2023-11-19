
#include "Motorsteuerung.h"
#include "GPIO.h"
#include"delay_ms.h"

int main(){

	EHRPWMinitForDCMotor();
	MotorInit_and_Mux (); // everything initialise


	/*set input*/

	// set speed-up
	PinMuxing(CONF_PORT1_PIN2,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p2, as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input

	// set speed-down
	PinMuxing(CONF_PORT1_PIN6,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p6, as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6,GPIO_INPUT);// set p1p6 input

	int speed = 82;
	while(1){
		if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW){
			speed = speed + 5;
			delay_ms(250); // xiaochu anjian doudong
		}else if(EGR_PinRead(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6) == PIN_LOW){
			speed = speed - 5;
			delay_ms(250); // xiaochu anjian doudong
		}
		MotorSpeedSet (speed);
	}

	return 0;
}
