#include "main.h"

void init_config(void)
{
	init_LED_config();
	init_DKP_config();
}

void main(void)
{
	init_config();
	
	while (1)
	{
		/*GETS THE KEY VALUE*/

		key = scan_digital_keypad();
		//Random delay
		if (!delay_DKP--)
		{
			delay_DKP = 2000;
			//when key is pressed
			if (key == 1)
			{
				//increments light till max
				if (DIM < max)
					DIM++;
			}
			//when key 2 is pressed
			else if (key == 2)
			{
				//decrements light till 0
				if (DIM > 0)
					DIM--;
			}
		}
		//glows the led
		if (count < DIM)
		{
			LEDS = ON_ALL;

		}
		else if (count > max)
		{
			count = 0;
		}
		else
		{
			LEDS = OFF_ALL;
		}
		count++;
	}
}
