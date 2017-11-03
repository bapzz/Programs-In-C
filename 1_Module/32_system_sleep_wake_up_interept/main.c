#include "main.h"

void init_config(void)
{
	init_SSD_config();
	init_DKP_config();
	init_timer0_config();
}

void main()
{
	init_config();

	while (1)
	{
		ssd_display();

		if (!delay--)
		{
			delay = 700;
			key = scan_digital_keypad();
			/* if key is pressed it wakes up */
			if (key == 1)
			{
				count = 0; 	
			}
			/* it goes to sleep in 10 seconds */
			if (count < 50)
				i = 4, j = 3, k = 2, l = 1;
			else
			{
				//i = 10, j = 10, k = 10, l = 10;	
				SLEEP();
			}
		}

	}
}
