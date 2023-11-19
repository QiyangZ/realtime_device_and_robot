/* EGR */

#include <hw_types.h>
#include"EGR_Cape.h"
#include"GPIO.h"
#include"delay_ms.h"
#include"Conf_mod.h"


int main() {

	unsigned int delay = 1000;
    unsigned int last_state = 1;

    //initialise p1p2
//	HWREG(0x44E10000 + 0x8B8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
//	HWREG(0x44E10000 + 0x8B8) |= 0x7;  // MUX 7 for GPIO p1p2
//	// set p1p2 input
//	HWREG(0x44E10000 + CONF_PORT1_PIN2) &=~ (1<<3); // pullup/pulldown enable p1p2
//	HWREG(0x44E10000 + CONF_PORT1_PIN2) |= (1<<4); // set pullup


	PinMuxing(CONF_PORT1_PIN2,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p2 as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input

	HWREG(0x44E10000 + 0x8B0) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + 0x8B0) |= 0x7;  // MUX 7 for GPIO p1p4

	HWREG(0x44E10000 + CONF_PORT2_PIN2) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + CONF_PORT2_PIN2) |= 0x7;  // MUX 7 for GPIO p2p2

	HWREG(0x44E10000 + CONF_PORT2_PIN4) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + CONF_PORT2_PIN4) |= 0x7;  // MUX 7 for GPIO p2p4

	HWREG(0x44E10000 + CONF_PORT2_PIN6) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + CONF_PORT2_PIN6) |= 0x7;  // MUX 7 for GPIO p2p6

	HWREG(0x44E10000 + CONF_PORT2_PIN8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + CONF_PORT2_PIN8) |= 0x7;  // MUX 7 for GPIO p2p8


	EGR_GPIODirSet(GPIO_PORT2_PIN2_MODUL,GPIO_PORT2_PIN2,0);// set p2p2 output
	EGR_GPIODirSet(GPIO_PORT2_PIN4_MODUL,GPIO_PORT2_PIN4,0);// set p2p4 output
	EGR_GPIODirSet(GPIO_PORT2_PIN6_MODUL,GPIO_PORT2_PIN6,0);// set p2p6 output
	EGR_GPIODirSet(GPIO_PORT2_PIN8_MODUL,GPIO_PORT2_PIN8,0);// set p2p8 output

	EGR_PinWrite(GPIO_PORT2_PIN2_MODUL,GPIO_PORT2_PIN2,1); // turn off LED1
	EGR_PinWrite(GPIO_PORT2_PIN4_MODUL,GPIO_PORT2_PIN4,1); // turn off LED2
	EGR_PinWrite(GPIO_PORT2_PIN6_MODUL,GPIO_PORT2_PIN6,1); // turn off LED3
	EGR_PinWrite(GPIO_PORT2_PIN8_MODUL,GPIO_PORT2_PIN8,1); // turn off LED4



	HWREG(0x44E10000 + CONF_PORT1_PIN4) &=~ (1<<3); // pullup/pulldown enable p1p4
	HWREG(0x44E10000 + CONF_PORT1_PIN4) |= (1<<4); // set pullup
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4,GPIO_INPUT); // set p1p4 input

//	HWREG(0x44E10000 + CONF_PORT1_PIN6) &=~ (1<<3); // pullup/pulldown enable p1p6
//	HWREG(0x44E10000 + CONF_PORT1_PIN6) |= (1<<4); // set pullup
//	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6,GPIO_INPUT);// set p1p6 input

//	HWREG(0x44E10000 + CONF_PORT1_PIN8) &=~ (1<<3); // pullup/pulldown enable p1p8
//	HWREG(0x44E10000 + CONF_PORT1_PIN8) |= (1<<4); // set pullup
//	EGR_GPIODirSet(GPIO_PORT1_PIN8_MODUL,GPIO_PORT1_PIN8,GPIO_INPUT);// set p1p8 input

while(1){ // most extern while

	if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW && last_state == 0){
		last_state = 1;
		}else{}

	if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW){
		last_state = 0;
	}else{}

	if(EGR_PinRead(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4) == PIN_LOW){
		 delay = 200;
	}else{}


if(last_state){

	EGR_PinWrite(GPIO_PORT2_PIN2_MODUL,GPIO_PORT2_PIN2,0); // turn on LED1
	delay_ms(delay);

	EGR_PinWrite(GPIO_PORT2_PIN2_MODUL,GPIO_PORT2_PIN2,1); // turn off LED1
	EGR_PinWrite(GPIO_PORT2_PIN4_MODUL,GPIO_PORT2_PIN4,0); // turn on LED2
	delay_ms(delay);

	EGR_PinWrite(GPIO_PORT2_PIN4_MODUL,GPIO_PORT2_PIN4,1); // turn off LED2
	EGR_PinWrite(GPIO_PORT2_PIN6_MODUL,GPIO_PORT2_PIN6,0); // turn on LED3
	delay_ms(delay);

	EGR_PinWrite(GPIO_PORT2_PIN6_MODUL,GPIO_PORT2_PIN6,1); // turn off LED3
	EGR_PinWrite(GPIO_PORT2_PIN8_MODUL,GPIO_PORT2_PIN8,0); // turn on LED4
	delay_ms(delay);
	EGR_PinWrite(GPIO_PORT2_PIN8_MODUL,GPIO_PORT2_PIN8,1); // turn off LED4

    }
}// most extern while
return 0;
}
