/* EGR */

#include <hw_types.h>
#include <hw_tsc_adc_ss.h>
#include <soc_AM335x.h> // basic adress of timer "SOC_DMTIMER_x_REGS"
#include"EGR_Cape.h"
#include <uartStdio.h>
#include"delay_ms.h"

int main() {
	//Clock aktivieren
	HWREG(SOC_CM_WKUP_REGS + (0xbc)) &= ~(0b11); //Bit 0 und 1 löschen
	HWREG(SOC_CM_WKUP_REGS + (0xbc)) |= (1<<1); //Bit 1 setzen

	//Schreibschutz der ADC-TSC Konfiguration deaktivieren
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 2);

	//STEP aktivieren
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPENABLE) |= ((1 << 1)|(1 << 2));

	//continous modul
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= ((0 << 1)|(1 << 0));

	//set filter 16 average
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= ((1 << 4)|(0 << 3)|(0 << 2));

	//referenz volt
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= ((0 << 12)|(0 << 13)|(0 << 14));

	//analog pin choose channel2 port1
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= ((0 << 22)|(0 << 21)|(0 << 20)|(1 << 19));

	// select memory FIFO_0
//	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_STEPCONFIG(0)) |= (0 << 26);

	// ADC starten(last bit to tsc_adc_ss select)
	HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_CTRL) |= (1 << 0);

	unsigned int meinAdcWert = 0;

	while (1)
	{
		/* Place main loop code here */
		//Aktuellen FIFO-Wert in eigene Variable schreiben
		meinAdcWert = HWREG(SOC_ADC_TSC_0_REGS + TSC_ADC_SS_FIFODATA(0));
		UARTprintf("Aktueller Wert: %d \n",meinAdcWert);
		delay_ms(200);
	}
	return 0;
}
