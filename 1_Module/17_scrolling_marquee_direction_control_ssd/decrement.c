#include "main.h"

void decrement(void)
{
	static unsigned short count;
	
	/* to display */
//	ssd_display();
	/* to give the delay using the program cycles */
	count++;

	if (count == 50000)
	{
		count = 0;
		i--, j--, k--, l--;
	}

	/* to decrement the values */
	if (i == 0)
	{
		i = 11;
	}
	if (j == 0)
	{
		j = 11;
	}
	if (k == 0)
	{
		k = 11;
	}
	if (l == 0)
	{
		l = 11;
	}		
}
