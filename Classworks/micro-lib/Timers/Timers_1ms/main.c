/*
 * Name   : Timers program.
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "main.h"			   /* Header File Inclusion */

void on_leds(void)
{
	if (count_timer0 == 1000)
	{
		count_timer0 = 0;
		LED1 = !LED1;
	}
#if 0
	if (count_timer1 == 100)
	{
		count_timer1 = 0;
		LED2 = !LED2;
	}

	if (count_timer2 == 100)
	{
		count_timer2 = 0;
		LED3 = !LED3;
	}

	if (count_timer3 == 100)
	{
		count_timer3 = 0;
		LED4 = !LED4;
	}
#endif
}

static void init_config(void)
{
	TRISB = 0xF0;		   	   /* Set PORTB0-4 as output    */
	ADCON1 = 0x0E;			   /* Disable analog module 	*/

	init_timer0();			   /* Initialize Timer0		*/
//	init_timer1();			   /* Initialize Timer1		*/
//	init_timer2();			   /* Initialize Timer2		*/
//	init_timer3();			   /* Initialize Timer3		*/
	GIE = 1;			   /* Global interrupt enable   */
}

/* Main function */
void main()
{
	init_config();

	while (1)
	{
		on_leds();
	}
}
/* End of the program */

