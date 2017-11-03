#include "main.h"

void init_config(void)
{
	init_DKP_config();
	init_LED_config();
}

void main(void)
{
	init_config();
	PORTD = 0xFF;
	int delay = DELY;

	while(1)
	{
		key = scan_digital_keypad();
		//To create the delay 
		if (!delay--)	
		{
			delay = DELY;
			switch (key)
			{
				case 1:
					train();
					break;

				case 2:
					train_reverse();
					break;
				case 3:
					toggle_nibbles();
					break;
				case 4:
					toggle_bits();
					break;
				case 5:
					on_off();
					break;
				case 6:
					
					break;
			}
		}
	}
}

