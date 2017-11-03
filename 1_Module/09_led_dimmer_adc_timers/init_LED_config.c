#include "main.h"

void init_LED_config(void)
{
	// config PORTB as an output PORT
	TRISB = 0x00;
	// config PORTB as an digital port
	ADCON1= 0x07;

	// clear the buffer
	LATB =0;

}
