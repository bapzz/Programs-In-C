#include "main.h"

void init_config(void)
{
	init_LED_config();
	init_ADC_config();
	init_timer0_config();
}

void main(void)
{
	init_config();
	unsigned short data;
	
	while (1)
	{
		data = adc() >> 2;

		if (count < data) //count less than dim led on
		{
			LEDS = ON_ALL;

		}
		else 
		{
			LEDS = OFF_ALL; // led will be off
		}
	        if (count > max)
		{
			count = 0;
		}
		count++;
	}
}
