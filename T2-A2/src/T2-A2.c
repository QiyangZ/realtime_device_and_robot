



/* EGR */

#include <hw_types.h>
#include <hw_dmtimer.h> // offsets adress of timer "SOC_DMTIMER_x_REGS"
#include <soc_AM335x.h> // basic adress of timer "SOC_DMTIMER_x_REGS"
#include <interrupt.h> //macro of timer  "SYS_INT_TINT..."
#include"EGR_Cape.h"
#include"GPIO.h"
#include"Conf_mod.h"
#include <hw_gpio_v2.h>
#include <uartStdio.h>
#include "delay_ms.h"

#define OVF_IT_FLAG 1
#define MAT_IT_FLAG 0

void myTimer2Isr(){
	//Abfrage der Interruptquelle
	if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << OVF_IT_FLAG)) != 0){
	//hier: eigener Code für Timer Overflow
		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL,GPIO_PORT3_PIN2,PIN_HIGH); // turn high
//		UARTprintf("overf \n");
	//Löschen des Timer-Interrupt-Flags
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << OVF_IT_FLAG);
	}
	else if ((HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) & (1 << MAT_IT_FLAG)) != 0){
	//hier: eigener Code für Compare Match
		EGR_PinWrite(GPIO_PORT3_PIN2_MODUL,GPIO_PORT3_PIN2,PIN_LOW); // turn low
//		UARTprintf("compare \n");
	//Löschen des Timer-Interrupt-Flags
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQSTATUS) = (1 << MAT_IT_FLAG);}
}



int main(){

	//set Interrupt
	IntAINTCInit(); // initialise controller
	IntMasterIRQEnable(); //set gloabel interruptcontroller aktiv
	IntSystemEnable(SYS_INT_TINT2); // set lokal interrupt aktiv
	IntRegister(SYS_INT_TINT2, myTimer2Isr); // feed the interrupt a function(ISR)
	//	IntPrioritySet(SYS_INT_TINT2, 0, AINTC_HOSTINT_ROUTE_IRQ);// set priority for this interrupt


	// set input
	PinMuxing(CONF_PORT1_PIN2,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p2, as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2,GPIO_INPUT);// set p1p2 input

	PinMuxing(CONF_PORT1_PIN4,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p4 as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4,GPIO_INPUT);// set p1p4 input

	PinMuxing(CONF_PORT1_PIN6,PULL_ENABLE,PULL_UP,GPIO_MODE); //initialise p1p6 as pull up,gpio
	EGR_GPIODirSet(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6,GPIO_INPUT);// set p1p6 input

	// set timer
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1<<1); // auto-reload activ
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) &=~ (1<<5); // make prescaler disable
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1<<6); // make compare enable
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCRR) = 0xFFFFFFFF - 480000; // initial value, 480000 times for one period
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TLDR) = 0xFFFFFFFF - 480000; // reload value
	unsigned int impuls = 36000; // equivalent 1.5ms
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + impuls; // compare value

	//set output
	PinMuxing(CONF_PORT3_PIN2,PULL_DISABLE,PULL_UP,GPIO_MODE); //initialise p3p2,disable pull,gpio
	EGR_GPIODirSet(GPIO_PORT3_PIN2_MODUL,GPIO_PORT3_PIN2,GPIO_OUTPUT);// set p3p2 output


	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_CLR) |= ((1<<0)|(1<<1)|(1<<2)); //clear IRQ status
	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_IRQENABLE_SET) |= ((1<<0)|(1<<1)); //set IRQ status

	HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TCLR) |= (1<<0); // timer start
	while(1){
			if(EGR_PinRead(GPIO_PORT1_PIN2_MODUL,GPIO_PORT1_PIN2) == PIN_LOW){
				impuls = 24000;
				UARTprintf("left \n");
				}else{}
			if(EGR_PinRead(GPIO_PORT1_PIN4_MODUL,GPIO_PORT1_PIN4) == PIN_LOW){
				impuls = 36000;
				UARTprintf("mittel \n");
				}else{}
			if(EGR_PinRead(GPIO_PORT1_PIN6_MODUL,GPIO_PORT1_PIN6) == PIN_LOW){
				impuls = 48000;
				UARTprintf("right \n");
				}else{}
			HWREG(SOC_DMTIMER_2_REGS + DMTIMER_TMAR) = 0xFFFFFFFF - 480000 + impuls; // compare value
		}

	return 0;
}
