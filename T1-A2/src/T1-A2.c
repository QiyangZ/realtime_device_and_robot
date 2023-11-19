/* EGR */
#include <hw_types.h>

int main(){
// for Port1 pin2 data6 8B8   gpio2_12
	HWREG(0x44E10000 + 0x8B8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6   gpio2_12
	HWREG(0x44E10000 + 0x8B8) |= 0x7;  // MUX 7 for GPIO
	HWREG(0x44E10000 + 0x8B8) &=~ (1<<3); // pullup/pulldown enable
	HWREG(0x44E10000 + 0x8B8) |= (1<<4); // set pullup

	HWREG(0x481AC000 + 0x134) |= (1<<12);  // Basisadresse GPIO 2 + offset GPIO_OE make it intput

// for Port1 pin4 data4 8B0   gpio2_10
	HWREG(0x44E10000 + 0x8B0) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data
	HWREG(0x44E10000 + 0x8B0) |= 0x7;  // MUX 7 for GPIO
	HWREG(0x44E10000 + 0x8B0) &=~ (1<<3); // pullup/pulldown enable
	HWREG(0x44E10000 + 0x8B0) |= (1<<4); // set pullup

	HWREG(0x481AC000 + 0x134) |= (1<<10);  // Basisadresse GPIO 2 + offset GPIO_OE make it intput

// for Port1 pin6 data2 8A8 gpio2_8
	HWREG(0x44E10000 + 0x8A8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data
	HWREG(0x44E10000 + 0x8A8) |= 0x7;  // MUX 7 for GPIO
	HWREG(0x44E10000 + 0x8A8) &=~ (1<<3); // pullup/pulldown enable
	HWREG(0x44E10000 + 0x8A8) |= (1<<4); // set pullup

	HWREG(0x481AC000 + 0x134) |= (1<<8);  // Basisadresse GPIO 2 + offset GPIO_OE make it intput

// for Port2 pin2 data14 8D8 gpio0_10
	HWREG(0x44E10000 + 0x8D8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data
	HWREG(0x44E10000 + 0x8D8) |= 0x7; // MUX 7 gpio
	HWREG(0x44E07000 + 0x134) &=~ (1<<10);  // Basisadresse GPIO 0 + offset GPIO_OE make it output

// for Port2 pin4 data13 8D4 gpio0_9
	HWREG(0x44E10000 + 0x8D4) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data
	HWREG(0x44E10000 + 0x8D4) |= 0x7; // MUX 7 gpio
	HWREG(0x44E07000 + 0x134) &=~ (1<<9);  // Basisadresse GPIO 0 + offset GPIO_OE make it output

// for Port2 pin6 data12 8D0 gpio0_8
	HWREG(0x44E10000 + 0x8D0) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data
	HWREG(0x44E10000 + 0x8D0) |= 0x7; // MUX 7 gpio
	HWREG(0x44E07000 + 0x134) &=~ (1<<8);  // Basisadresse GPIO 0 + offset GPIO_OE make it output

// start with LEDs turn off
	HWREG(0x44E07000 + 0x13c) |= (1<<10); // 0 -- GND 1--turn off
	HWREG(0x44E07000 + 0x13c) |= (1<<9);
	HWREG(0x44E07000 + 0x13c) |= (1<<8);


	while(1){
		if ((HWREG(0x481ac000+0x138)&(1<<12))==0){
			HWREG(0x44e07000+0x13c)&=~(1<<10);
		} else {HWREG(0x44e07000+0x13c)|=(1<<10);}


		if ((HWREG(0x481ac000+0x138)&(1<<10))==0){
			HWREG(0x44e07000+0x13c)&=~(1<<9);
		} else {HWREG(0x44e07000+0x13c)|=(1<<9);}


		if ((HWREG(0x481ac000+0x138)&(1<<8))==0){
			HWREG(0x44e07000+0x13c)&=~(1<<8);
		} else {HWREG(0x44e07000+0x13c)|=(1<<8);}

	}
	return 0;
}
