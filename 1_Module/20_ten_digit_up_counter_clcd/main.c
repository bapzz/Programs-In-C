#include "main.h"

void init_config()
{
	init_clcd_config();
}

void main()
{
	char message[] = "UP-COUNTER";
	char counter[] = "0000000000";
	init_config();

	int i;

	while(1)
	{
		//increments the last value
		counter[9]++;
		//checks for the every digit
		for (i = 9; i >= 0; i--)
		{
			//resets the digits
			if (counter[i] > '9')
			{
				counter[i] = '0';
				counter[i-1]++;
			}
		}
		//when the last digit becomes > 9
		//reset and start again
		if (counter [0] > '9')
		{
			counter[0] = '0';
		}	

		puts(line2_home+3, counter);
		puts(line1_home+3, message);
		delay(500);
	}

}
