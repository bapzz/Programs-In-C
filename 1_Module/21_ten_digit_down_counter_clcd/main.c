#include "main.h"

void init_config()
{
	init_clcd_config();
}

void main()
{
	char message[] = "DOWN-COUNTER";
	char counter[] = "9999999999";
	init_config();

	int i;

	while(1)
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
		//when the last digit becomes 0
		//reset and start again
		if (counter [0] < '0')
		{
			counter[0] = '9';
		}	
		puts(line1_home+2, message);
		puts(line2_home+3, counter);
		//delay(500);
	}

}
