/*implemnt data stroage on power using zcd input*/
#include "main.h"

/* Function definition to configure pins */
void init_config(void)
{
	init_uart_config();
	init_DKP_config();
}

void main()
{
	unsigned char key;
	int i, j;

	/* Function call to configure pins */
	init_config();

	/* Infinite loop */
	while(1)
	{
		/* To get a key from DKP */
		key = scan_digital_keypad();

		for(i = 0; i < 400; i++)
		{
			for(j = 0; j < 300; j++);
		}

		/* Send key value to TXREG when key is pressed */
		if (key != 0xFF)
		{
			is_busy();
			//write_lcd(key, DATA_MODE);
			clear_display;
			is_busy();
			putchar(line2_home, key);
			TXREG = key;

			while(!PIR1bits.TXIF);
		}
	}
}
