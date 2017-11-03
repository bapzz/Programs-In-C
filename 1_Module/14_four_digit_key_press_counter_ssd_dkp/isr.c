#include "main.h"
extern unsigned short count;

void interrupt isr(void)
{
	if (TMR0IF == 1)
	{
		TMR0IF = 0;
		count++;
	}
}
