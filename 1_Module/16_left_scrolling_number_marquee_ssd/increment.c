#include "main.h"

char i = 3, j = 2, k = 1, l = 0, m = 0;

void increment(void)
{
	static unsigned short count;
	
	/* to display */
	ssd_display();
	/* to give the delay using the program cycles */
	count++;

	if (count == 1000)
	{
		count = 0;
		m++;
	}
	/* to increment the values */
	if (m == 10)
	{
	 	m = 0;
		i++, j++, k++, l++;
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
}
