/* EGR */

#include <hw_types.h>
#include "i2c.h"
#include "delay_ms.h"
#include <uartStdio.h>


//int main() {
//	//Aufgabe1
//
////	unsigned int slave_address = 56;
////	unsigned char configuration[2] = {0b00000011,0b01111111};// register3 - setting register
////	unsigned char turn_on[2] = {1,0b10000000};//rigister1,  pin7 1
////	unsigned char turn_off[2] = {1,0b00000000};//rigister1,  pin7 0
////	unsigned char data_length = 2;
////	char stp = 1;
////	initi2c(); //initialise
////	writetoi2c(slave_address,configuration,data_length,stp);//set pin7 output
//
//
//	//Aufgabe2
//
//	unsigned char set_input[1]={0b00000000};//register0
//
//	unsigned int slave_address = 56;
//	unsigned char turn_on[2] = {1,0b10000000};//rigister1,  pin7 1
//	unsigned char turn_off[2] = {1,0b00000000};//rigister1,  pin7 0
//	unsigned char configuration[2] = {0b00000011,0b01111111};// register3 - setting register
//
//	initi2c();
//	writetoi2c(slave_address,configuration,2,1);//set pin7 output
//
//
//	char signal[1]={};
//
//	while(1)
//	{
//		/* Place main loop code here */
//
//		//Aufgabe1
//		/*
//		writetoi2c(slave_address,turn_on,data_length,stp);
//		delay_ms(600);
//		writetoi2c(slave_address,turn_off,data_length,stp);
//		delay_ms(600);
//		*/
//
//		//Aufgabe2
//
//		writetoi2c(slave_address,turn_on,2,1);
////		CleanUpInterrupts();
//
//		writetoi2c(slave_address,set_input,1,0);
//		readfromi2c(slave_address,signal,1,1);
//		UARTprintf(" The signal is: ");
//		UARTprintf(BYTETOBINARYPATTERN,BYTETOBINARY(signal[0]));
//		UARTprintf("\n");
//
//		writetoi2c(slave_address,turn_off,2,1);
////		CleanUpInterrupts();
//
//		unsigned int bottom_left = signal[0] & 0b01000000 ? 1 : 0;
//		unsigned int bottom_mitl = signal[0] & 0b00100000 ? 1 : 0;
//		unsigned int bottom_rigt = signal[0] & 0b00010000 ? 1 : 0;
//		unsigned int frontt_left = signal[0] & 0b00001000 ? 1 : 0;
//		unsigned int frontt_mitl = signal[0] & 0b00000100 ? 1 : 0;
//		unsigned int frontt_rigt = signal[0] & 0b00000010 ? 1 : 0;
//
//		delay_ms(500);//consider: need delay in T5 ??????????
//
//
//
//
//	}
//	return 0;
//}


int main(){
	IR_initialise();
	char signal[1] = {};

	while(1){
		signal[0] = get_IR_data();
		unsigned int bottom_left = signal[0] & 0b01000000 ? 1 : 0;
		unsigned int bottom_mitl = signal[0] & 0b00100000 ? 1 : 0;
		unsigned int bottom_rigt = signal[0] & 0b00010000 ? 1 : 0;
		unsigned int frontt_left = signal[0] & 0b00001000 ? 1 : 0;
		unsigned int frontt_mitl = signal[0] & 0b00000100 ? 1 : 0;
		unsigned int frontt_rigt = signal[0] & 0b00000010 ? 1 : 0;
		UARTprintf(" Bottom: %d %d %d \t Front:%d %d %d \n",bottom_left,bottom_mitl,bottom_rigt,frontt_left,frontt_mitl,frontt_rigt);
		delay_ms(50);
	}
}
