#include "main.h"

void init_config(void)
{
	init_timer0_config();
	init_LED_config();
}

void main(void)
{
	init_config();

	while(1)
	{
		blink_led ();
	}
}

