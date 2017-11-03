/*
 * Name   : Interrupt service routine files
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "isr.h"

volatile unsigned char count_timer0 = 0;
volatile unsigned char count_timer1 = 0;
volatile unsigned char count_timer2 = 0;
volatile unsigned char count_timer3 = 0;

void interrupt timers(void)
{
	if (TMR0IF)			/* Check wheather Timer0 interrupt flag is enabled or not*/
	{
		count_timer0++;
		TMR0 = 0x7E;
		TMR0IF = 0;
	}
#if 0
	if (TMR1IF)			/* Check wheather Timer1 interrupt flag is enabled or not*/
	{
		count_timer1++; 
		TMR1L = 0x96;
		TMR1H = 0xE7;
		TMR1IF = 0; 
	}

	if (TMR2IF)			/* Check wheather Timer2 interrupt flag is enabled or not*/
	{
		count_timer2++;
		TMR2 = 0x00;
		PR2 = 195;
		TMR2IF = 0;
	}

	if (TMR3IF)			/* Check wheather Timer3 interrupt flag is enabled or not*/
	{
		count_timer3++; 
		TMR3L = 0x96;
		TMR3H = 0xE7;
		TMR3IF = 0; 
	}
#endif
}
