/*
 *	Delay functions
 *	See delay.h for details
 *
 *	Make sure this code is compiled with full optimization!!!
 */

#include"delay.h"

void delay_ms(unsigned char count)
{
#if	XTAL_FREQ <= 2MHZ
	do
	{
		delay_us(996);
	}
	while(--count);
#endif

#if    XTAL_FREQ > 2MHZ	
	unsigned char i;
	do 
	{
		i = 4;
		do
		{
			delay_us(250);
		}
		while(--i);
	}
	while(--count);
#endif
}
