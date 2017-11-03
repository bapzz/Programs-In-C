#include "main.h"

void init_config()
{
	init_clcd_config();
	init_mkp_config();
}

void main()
{
	char message[] = "DOWN-COUNTER";
	char counter[] = "9999999999";
	init_config();

	while(1)
	{
		key = scan_matrix_keypad();
		/* increments the number */
		if (key == '1')
		{
			counter[i]++;
			if (counter[i] == ':')
				counter[i] = '0';
		}
		/* decrements the number */
		if (key == '2')
		{
			counter[i]--;
			if (counter[i] == 47)
				counter[i] = '9';
		}
		/* increments the field */
		if (key == '3')
		{
			i++;
			if (i == 10)
				i = 0;
		}
		/* starts the timer */
		if (key == '4')
		{
			//decrements the last value
			counter[9]--;
			//checks for the every digit
			for (i = 9; i >= 0; i--)
			{
				//resets the digits
				if (counter[i] < '0')
				{
					counter[i] = '9';
					counter[i-1]--;
				}
			}

		}
		puts(line1_home+2, message);
		puts(line2_home+3, counter);
		delay(500);
	}
}
