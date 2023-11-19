// Verlinkt
#ifndef IRSENSORS_H_
#define IRSENSORS_H_

#include <hw_types.h>
#include "i2c.h"
#include "delay_ms.h"
//#include <uartStdio.h>

unsigned int slave_address = 56;
unsigned char turn_on[2] = {1,0b10000000};//rigister1,  pin7 1
unsigned char turn_off[2] = {1,0b00000000};//rigister1,  pin7 0
unsigned char configuration[2] = {0b00000011,0b01111111};// register3 - setting register
unsigned char data_length = 2;

unsigned char set_input[1]={0b00000000};


void IR_initialise();
//void IR_turn_on();
//void IR_turn_off();
char get_IR_data();

#endif /* IRSENSORS_H_ */
