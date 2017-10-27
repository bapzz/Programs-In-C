#include "main.h"

void init_config(void)
{
	init_DKP_config();
	init_LED_config();
}

void main(void)
{
	init_config();
	unsigned char key;
	PORTD = 0xFF;

	while(1)
	{
		//Scan for the key press
		key = scan_digital_keypad();

		switch (key)
		{
			case 1:
				LED1 = ON;
				break;
			case 2:
				LED2 = ON;
				break;
			case 3:
				LED3 = ON;
				break;
			case 4:
				LED4 = ON;
				break;

		}
	}
}

