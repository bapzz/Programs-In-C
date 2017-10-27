#include "main.h"

void interrupt isr (void)
{
	if (TMR0IF) {
		TMR0IF = 0;
		count++;
	}
}
