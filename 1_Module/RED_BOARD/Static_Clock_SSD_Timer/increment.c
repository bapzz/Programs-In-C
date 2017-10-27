#include "main.h"

char i = 0, j = 0, k = 2, l = 1, m = 0;

void increment(void)
{

	/* to display */
	ssd_display();
	/* to give the delay using the program cycles */

	if (count == 76)
	{
		count = 0;
		i++;
	}
	/* to increment the values */
	if (i == 10)
	{
		i = 0;
		j++;

		if (j == 6)
		{
			j = 0;
			k++;
		}
		if (k == 10)
		{
			k = 0;
			l++;
		}
		/*		if (l == 2 && k == 4)
				{
				l = 0;		//for hour
				k = 0;
				}
		*/
		if (l == 10)
		{
			l = 0;
		}

	}		
}
