#include "main.h"
extern char i, j, k, l;
unsigned short count;

void init_config(void)
{
	init_SSD_config();
	init_DKP_config();
	init_timer0_config();
}

void main()
{
	init_config();

	int flag;
	
	while (1)
	{
		ssd_display();
		if (!delay--)
		{
			delay = 700;
			key = scan_digital_keypad();
		}

		/* enables the timer0 module */
		if (key == 1)
		{
			TMR0ON = 1;
		}
		if ((key == 0) && (key1 == 1))	/* increments the count as key released */
		{
			TMR0ON = 0;
			key1 = 0;
			if (flag == 0)
				increment();
			flag = 0;
			count = 0;
		}
		/* resets the count */
		if (count > 50)
		{
			flag = 1;
			count = 0;
			TMR0ON = 0;
			i = 0;j = 0;k = 0;l = 0;
			key = 0;
			key1 = 0;
		}

	}
}
