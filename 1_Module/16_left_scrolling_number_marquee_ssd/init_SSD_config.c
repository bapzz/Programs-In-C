#include "main.h"

void init_SSD_config(void)
{
	//config PORTD as an output
	TRISD = 0;
	//Config PORTA as an output
	TRISA = TRISA & 0xF0;
}
