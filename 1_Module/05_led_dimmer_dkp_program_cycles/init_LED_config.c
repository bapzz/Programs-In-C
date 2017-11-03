#include "main.h"

void init_LED_config(void)
{
	//config PORTB as an output
	TRISB = 0x00;

	//Config PORTB as an digital port
	//ADCON1 = 0x0E;
	ADCON1 = 0x07;
	
	//Clear the buff
	LATB = 0;

}
