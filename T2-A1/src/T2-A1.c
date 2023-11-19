/* EGR */

#include <hw_types.h>
#include"EGR_Cape.h"
#include"GPIO.h"
#include"delay_ms.h"
#include <interrupt.h>
#include <soc_AM335x.h>
#include <hw_gpio_v2.h>

void myGPIO2Isr(){
	EGR_PinWrite(GPIO_PORT2_PIN2_MODUL,GPIO_PORT2_PIN2,1); // turn off LED1
	EGR_PinWrite(GPIO_PORT2_PIN4_MODUL,GPIO_PORT2_PIN4,1); // turn off LED2
	EGR_PinWrite(GPIO_PORT2_PIN6_MODUL,GPIO_PORT2_PIN6,1); // turn off LED3
	EGR_PinWrite(GPIO_PORT2_PIN8_MODUL,GPIO_PORT2_PIN8,1); // turn off LED4
	while(1){};
	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS(0)) |= (1<<GPIO_PORT1_PIN6); //falg delete
}

int main() {

	unsigned int delay = 1000;
    unsigned int last_state = 1;

	HWREG(0x44E10000 + 0x8B8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + 0x8B8) |= 0x7;  // MUX 7 for GPIO p1p2

	HWREG(0x44E10000 + 0x8B0) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + 0x8B0) |= 0x7;  // MUX 7 for GPIO p1p4

	HWREG(0x44E10000 + 0x8B0) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + 0x8B0) |= 0x7;  // MUX 7 for GPIO p1p6

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

	HWREG(0x44E10000 + CONF_PORT1_PIN2) &=~ (1<<3); // pullup/pulldown enable p1p2
	HWREG(0x44E10000 + CONF_PORT1_PIN2) |= (1<<4); // set pullup
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input

	HWREG(0x44E10000 + CONF_PORT1_PIN4) &=~ (1<<3); // pullup/pulldown enable p1p4
	HWREG(0x44E10000 + CONF_PORT1_PIN4) |= (1<<4); // set pullup
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4,GPIO_INPUT); // set p1p4 input

	HWREG(0x44E10000 + CONF_PORT1_PIN6) &=~ (1<<3); // pullup/pulldown enable p1p6
	HWREG(0x44E10000 + CONF_PORT1_PIN6) |= (1<<4); // set pullup
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6,GPIO_INPUT);// set p1p6 input

//	HWREG(0x44E10000 + CONF_PORT1_PIN8) &=~ (1<<3); // pullup/pulldown enable p1p6
//	HWREG(0x44E10000 + CONF_PORT1_PIN8) |= (1<<4); // set pullup
//	EGR_GPIODirSet(GPIO_PORT1_PIN8_MODUL,GPIO_PORT1_PIN8,GPIO_INPUT);// set p1p8 input

	IntAINTCInit(); // initialise controller
	IntMasterIRQEnable(); //set gloabel interruptcontroller aktiv
	IntSystemEnable(SYS_INT_GPIOINT2A); // set lokal interrupt aktiv
	IntRegister(SYS_INT_GPIOINT2A, myGPIO2Isr); // feed the interrupt a function(ISR)
	IntPrioritySet(SYS_INT_GPIOINT2A, 0, AINTC_HOSTINT_ROUTE_IRQ);// set priority for this interrupt
	HWREG(SOC_GPIO_2_REGS + GPIO_IRQSTATUS_SET(0)) |= (1<<GPIO_PORT1_PIN6); //set prot1 pin6


	HWREG(SOC_GPIO_2_REGS + GPIO_LEVELDETECT(0)) |= (1<<GPIO_PORT1_PIN6); //set prot1 pin6 as a trigger

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

//	if(EGR_PinRead(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6) == PIN_LOW){
//		HWREG(SOC_GPIO_2_REGS + GPIO_LEVELDETECT(1)) |= (1<<GPIO_PORT1_PIN6); //set prot1 pin6 a
//	}else{} ganz falsh


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

