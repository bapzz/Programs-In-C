#include "main.h"

void delay(unsigned short time)
{
	volatile unsigned short i, j;

	for (i = 0; i < time; i++)
	{
		for (j = 0; j < 350; j++)
		{
			;
		}
	}
}
