#include "main.h"

void train(void)
{
	static int flag = 0;
	//Train Right - Left LEDS ON
	if ((flag == 0))
	{
		LEDS = LEDS >> 1;
		if (LEDS == 0x00)
		{
			flag = 1;
		}
	}
	//LEDS OFF
	if ((flag == 1))	
	{
		LEDS = 0x80 | (LEDS >> 1);
		if (LEDS == 0xFF)
		{
			flag = 0;
			state_flag = 1;
		}
	}

}


void train_reverse(void)
{
	static int flag = 0;
	//Train Left - Right LEDS ON
	if ((flag == 0))
	{
		LEDS = LEDS << 1;
		if (LEDS == 0x00)
		{
			flag = 1;
		}
	}
	//LEDS OFF
	if ((flag == 1))
	{
		LEDS = 0x1 | (LEDS << 1);
		if (LEDS == 0xFF)
		{
			flag = 0;
			state_flag = 0;
		}

	}
}
