#include "main.h"
extern unsigned short count;
void timer0_delay(void)
{
    if (TMR0IF)
    {
	TMR0IF = 0;
	count++;
    }
}
