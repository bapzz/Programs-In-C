#include "main.h"

void init_config(void)
{
	init_LED_config();
}

void main(void)
{
	init_config();

	while(1)
	{
		led_blink();
	}	
}

