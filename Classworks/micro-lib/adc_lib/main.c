/*
 * Name   : Test analog module 
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 *
 */

#include "main.h"

void glow_led(unsigned short adc_reg_val)
{
	if (adc_reg_val > 512)
	{
		LED1 = ON;
	}
	else
	{
		LED1 = OFF;
	}
}

static void init_config(void)
{
	/* Direction setting for LED1 */
	TRISBbits.TRISB0 = 0;

	/* Disable analog module at PORTB */
	 ADCON1 = 0x1E;

	/* Turn off LED1 */
	LED1 = OFF;

	/* Initialize analog module */
	init_adc();
}

void main(void)
{
	unsigned short adc_reg_val;

	init_config();

	while (1)
	{
		adc_reg_val = read_adc(CHANNEL4);
		glow_led(adc_reg_val);
	}
}
