#include "main.h"

void init_config(void)
{
	init_LED_config();
	init_DKP_config();
	init_timer0_config();
}

void main(void)
{
	init_config();
	int delay_DKP;
	
	while (1)
	{
		/*GETS THE KEY VALUE*/
		key = scan_digital_keypad();
		if (!delay_DKP--)
		{
			delay_DKP = 2000;

			if (key == 1)
			{
				DIM = max;
				TMR0ON = 1;	
			}
		}
		
		if ((TMR0ON = 1) && (count == 380))
		{
			DIM = 25;
			count = 0;
			TMR0ON = 0;
		}
		
		if (count1 < DIM)
		{
			LEDS = ON_ALL;

		}
		else if (count1 > max)
		{
			count1 = 0;
		}
		else
		{
			LEDS = OFF_ALL;
		}
		count1++;
	}
}
