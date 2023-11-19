/* EGR */

#include <hw_types.h>

int main() {
	HWREG(0x44E10000 + 0x8B8) &=~ ( (1<<0) | (1<<1) | (1<<2) ); //Basisadresse des Contorl Modules + offset des data6
	HWREG(0x44E10000 + 0x8B8) |= 0x7;  // MUX 7 for GPIO

	HWREG(0x481AC000 + 0x134) &=~ (1<<12);  // Basisadresse GPIO 2 + offset GPIO_OE make it output
	HWREG(0x481AC000 + 0x13c) &= ~(1<<12);  // make pin2 GND


	while (1)
	{
		/* Place main loop code here */
	}
	return 0;
}
