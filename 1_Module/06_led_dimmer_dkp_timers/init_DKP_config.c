#include "main.h"

void init_DKP_config(void)
{
	//Config lower 4 bits of PORTC as an input port
	TRISC = (TRISC & 0xF0) | 0x0F;

}
