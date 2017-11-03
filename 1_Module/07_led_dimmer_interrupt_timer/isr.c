#include "main.h"

//extern unsigned short count;

void interrupt isr (void)
{
	if (TMR0IF) 
	{
		TMR0IF = 0;
		count++;
	}
}
