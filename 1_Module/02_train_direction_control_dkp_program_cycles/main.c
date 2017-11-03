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
		//Scan for the key press
		key = scan_digital_keypad();
		if (key)
		{
			if (state_flag)
			{
				state_flag = 0;

				if (flag == 0)
					flag = 1;
				else
					flag = 0;
			}
			else
			{
				if (!state_flag)
				{
					state_flag = 1;

					if (flag == 0)
						flag = 1;
					else
						flag = 0;
				}
			}
		}

		if (!delay--)
		{
			delay = DELY;
			if (state_flag == 0)
			{
				train_reverse();
			}
			else
			{
				train();
			}
		}
	}
}

