#include "main.h"

void init_LED_config(void)
{
	//config PORTD as an o/p PORT
	TRISB = 0x00;

	//switch off comparator
	ADCON1 = 0x07;
	//switch off LEDS
	//PORTD = 0xFF;
	LATB = 0;
}
