// Verlinkt
#include "IRSensors.h"


void IR_initialise(){
	initi2c();
	writetoi2c(slave_address,configuration,2,1);//set pin7 output
}

//void IR_turn_on(){
//	writetoi2c(slave_address,turn_on,data_length,1);
//}
//
//void IR_turn_off(){
//	writetoi2c(slave_address,turn_off,data_length,1);
//}

char get_IR_data(){
	char signal[1] = {};
	writetoi2c(slave_address,turn_on,2,1);
//		CleanUpInterrupts();

	writetoi2c(slave_address,set_input,1,0);
	readfromi2c(slave_address,signal,1,1);
//	UARTprintf(BYTETOBINARYPATTERN,BYTETOBINARY(signal[0]));

	writetoi2c(slave_address,turn_off,2,1);

	return signal[0];
}
