#include "main.h"

void init_DKP_config(void)
{
	//config PORTB as an i/p PORT
	TRISC = (TRISC & 0xF0) | 0x0F;

	//switch off LEDS
	//PORTD = 0xFF;
}
