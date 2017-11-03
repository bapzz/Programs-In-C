#include "main.h"

void init_SSD_config(void)
{
	//COnfig PORTD as an output
	TRISD = 0;
	
	//COnfig PORTA as an output
	TRISA = TRISA & 0xF0;
}
