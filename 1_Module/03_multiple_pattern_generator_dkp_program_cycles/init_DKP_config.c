#include "main.h"

void init_DKP_config(void)
{
	//config PORTB as an input port
	TRISB = 0xFF;

	//Enable Internal Pull Up Resistor
	//RBPU = 0;

	//switch off the LEDS
	PORTD = 0xFF;

	//disable the compartor of PORTD
	CMCON = 0x07;
}
