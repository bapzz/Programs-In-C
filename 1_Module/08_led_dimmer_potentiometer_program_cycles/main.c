#include "main.h"

void init_config(void)
{
	init_LED_config();
	init_ADC_config();
}

void main(void)
{
	init_config();
	unsigned short data;
	
	while (1)
	{
		data = adc() >> 1;

		if (count < data)
		{
			LEDS = ON_ALL;
		}
		else
		{
			LEDS = OFF_ALL;
		}
		if (count > max)
		{
			count = 0;
		}
		count++;
	}
}
