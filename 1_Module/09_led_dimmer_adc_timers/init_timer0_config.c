#include "main.h"

void init_timer0_config(void)
{
	// Config T0CON register , this reg controls the timer0

	// Enable the timer0 module
	TMR0ON = 1;	
	// Timer0 is configured as an 8-bit timer
	T08BIT = 1;
	
	// Select INternal instruction cycle clock as a source
	T0CS = 0;
	
	// Timer0 Prescalar Assignment bit
	PSA = 0;
	
	// Select 1:256 prescalar
	T0PS2 = 1;
	T0PS1 = 1;
	T0PS0 = 1;

	// Enable Timer0 interrupt
	TMR0IE = 1;
	
	// Enable peripheral interrupt
	//PEIE = 1;
	
	// Enable Global interrupt
	GIE = 1;
	
	// Set timer0 interrupt flag to 0
	TMR0IF = 0;
}
