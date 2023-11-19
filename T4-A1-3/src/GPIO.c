// Diese Datei wird nur verlinkt. D.h. ihr editiert ueber alle Projekte hinweg die selbe (diese) Datei.

/*
 * EGR_GPIO.c
 *
 *  Created on: 24.01.2014
 *      Author: Jonas Pfeiffer, Johannes Coy
 *   Copyright: TUM MiMed
 * Last Change: 28.10.2014
 */
#include "GPIO.h"

/*****************************************************************************
**                       FUNCTION DEFINITIONS
*****************************************************************************/

void EGR_GPIODirSet(unsigned int gpio_base_addr,
					unsigned int pinNumber,
					unsigned int pinDirection)
{
	//TODO: Ergaenzen Sie hier den code zum Einstellen der Pin-Funktion (Input oder Output)
	if (pinDirection == GPIO_OUTPUT){
		HWREG(gpio_base_addr + 0x134) &=~ (1<<pinNumber); //set to output
	}else{
		HWREG(gpio_base_addr + 0x134) |= (1<<pinNumber); //set to input
	}

}

void EGR_PinWrite  (unsigned int gpio_base_addr,
					unsigned int pinNumber,
					unsigned int pinValue)
{
	//TODO: Ergaenzen Sie hier den code zum Einstellen des Pin-Ausgabe Werts (0V oder 3,3V)
	//Tipp: Verzweigung ob an- oder aus-geschaltet werden soll
	if(pinValue == PIN_HIGH){
		HWREG(gpio_base_addr + 0x13c) |= (1<<pinNumber);  // make pin to high
	}else{
		HWREG(gpio_base_addr + 0x13c) &=~ (1<<pinNumber);  // make pin to low
	}

}



unsigned int EGR_PinRead (unsigned int gpio_base_addr,
						  unsigned int pinNumber)
{
	//TODO: Ergaenzen Sie hier den code zum Auslesen des Pin-Werts (0V oder 3,3V)
	//Auslesen des Pinwerts und Rueckgabe ueber return
	unsigned int PinW_ausl;
	if((HWREG(gpio_base_addr+0x138)&(1<<pinNumber))==0){
		PinW_ausl = PIN_LOW;
	}else{
		PinW_ausl = PIN_HIGH;
	}
	return PinW_ausl;

}

/******************************* End Of File ********************************/
