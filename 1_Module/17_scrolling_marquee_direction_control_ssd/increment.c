#include "main.h"

void increment(void)
{
	static unsigned short count;

	/* to display */
	//	ssd_display();
	/* to give the delay using the program cycles */
	count++;

	if (count == 50000)
	{
		count = 0;
		i++, j++, k++, l++;
	}
	/* to increment the values */

	if (i == 11)
	{
		i = 0;
	}
	if (j == 11)
	{
		j = 0;
	}
	if (k == 11)
	{
		k = 0;
	}
	if (l ==11)
	{
		l = 0;
	}		
}
