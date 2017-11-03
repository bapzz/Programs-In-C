#include "main.h"

void init_LED_config(void)
{
	//config PORTB as an output
	TRISD = 0x00;

	//disable the compartor of PORTD
	CMCON = 0x07;

	//Config PORTB as an digital port
	//ADDCON1 = 0x07;

	//switch off the LEDS
	PORTD = 0xFF;

}
