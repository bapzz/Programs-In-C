#include "main.h"

#define _XTAL_FREQ 20000000

#pragma config OSC = XT
#pragma config WDT = OFF
#pragma config BOREN = OFF
#pragma config PBADEN = OFF
#pragma config LVP = OFF

void init_config(void)
{
	/* Set PORTB as a Output */
	TRISB = 0x00;

}

void delay(unsigned int ms)
{
	int i, j;
	for (i = 0; i < ms; i++)
	{
		for (j = 0; j < 350; j++);
	}

}
void main(void)
{
	init_config();

	while(1)
	{
		LED_PORT = 0x00;
		delay(1000);
		LED_PORT = 0xFF;
		delay(1000);

	}
}

