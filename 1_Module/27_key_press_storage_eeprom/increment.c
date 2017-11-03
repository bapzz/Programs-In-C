#include "main.h"

char i, j, k, l;

void increment(void)
{
	i++;
	//To increment the values
	if (i == 10)
	{
		i = 0;
		j++;
		if (j == 10)
		{
			j = 0;
			k++;
			if (k == 10)
			{
				k = 0;
				l++;
				if (l == 10)
				{
					l = 0;
				}
			}
		}
	}
}
