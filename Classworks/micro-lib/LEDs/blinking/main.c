/*
 * Name   : Leds blinking program.
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "main.h"

static void init_config(void)
{
	/* Set PORTB as output */
	TRISB = 0x00;

	/* Disable analog function at PORTB */
	ADCON1 = 0x1E;
}

/* Simple delay function it is not real */
void delay(unsigned int ms)
{
	int i, j;

	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 350; j++);
	}

}

/* Main function */
void main(void)
{
	init_config();

	/* Infinity loop */
	while (1)
	{
		LED_PORT = 0x00;	/* Off all leds */
		delay(1000);
		LED_PORT = 0xFF;	/* On all leds */
		delay(1000);
	}
}
/* End of the program */
