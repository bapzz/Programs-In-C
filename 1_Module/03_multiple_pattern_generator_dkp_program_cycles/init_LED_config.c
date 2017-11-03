#include "main.h"

void init_LED_config(void)
{
	//config PORTB as an output
	TRISD = 0x00;

	//switch off the comparator
	CMCON = 0x07;

	//Clear the buff
	//LATD = 0;

}
