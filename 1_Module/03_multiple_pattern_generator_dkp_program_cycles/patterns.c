#include "main.h"

void train(void)
{
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
		}
	}
}
/*Train in reverse direction */
void train_reverse(void)
{
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
		}
	}
}
/* toggles nibble */
void toggle_nibbles(void)
{
	if(flag)
	{	
		LEDS = 0xF0;
		flag = 0;
	}	
	else
	{
		LEDS = 0x0F;
		flag = 1;
	}
}
/* Toggles each Bits */
void toggle_bits(void)
{
	if(flag)
	{	
		LEDS = 0xAA;
		flag = 0;
	}	
	else
	{
		LEDS = 0x55;
		flag = 1;
	}
}
/* Turns On all LED and OFFS them*/
void on_off(void)
{
	if(flag)
	{	
		LEDS = 0x00;
		flag = 0;
	}	
	else
	{
		LEDS = 0xFF;
		flag = 1;
	}

}
