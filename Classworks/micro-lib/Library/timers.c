/*
 * Name   : Timer 0, 1, 2 and 3 configuration file 
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "timers.h"

void init_timer0(void)
{
	T0CON = 0xC7;		            
	TMR0IE = 1;              	/* Timer0 Interrupt Enable bit      */
	TMR0 = 0x3B;			/* Load calculated value for 10ms to timer0 register */
}

void init_timer1(void)
{
	T1CON = 0xB1;			/* Prescalar value is selected as 1:8         */
	TMR1IE = 1;			/* Timer1 Interrupt enable                    */
	TMR1L = 0X96;			/* Load calulated value(lower byte) to TMR1L  */
	TMR1H = 0xE7;			/* Load calculated value(upper byte) to TMR1H */
}

void init_timer2(void)
{
	T2CON = 0x7A;			/* Prescalar value is selected as 1:16        */
	TMR2IE = 1;			/* Timer2 Interrupt enable                    */
	TMR2 = 0;			/* Reload zero value to TMR2		      */
	PR2 = 195;			/* Load calculated to PR2		      */
	TMR2ON = 1;			/* On timer 2 to incrementing 		      */
}

void init_timer3(void)
{
	T3CON = 0xB1;			/* Prescalar value is selected as 1:8         */
	TMR3IE = 1;			/* Timer1 Interrupt enable                    */
	TMR3L = 0X96;			/* Load calulated value(lower byte) to TMR3L  */
	TMR3H = 0xE7;			/* Load calculated value(upper byte) to TMR3H */
}
