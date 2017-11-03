#include "main.h"

/* Function definition to configure pins */
void init_config(void)
{
	init_uart_config();
	init_MKP_config();
	init_CLCD_config();
}

unsigned char prev, key;

/* Execution of program starts from here */
void main()
{
	unsigned char ch, flag = 0, arr[16];
	char i = 0, count = 0, flag2 = 0;

	/* Function call to configure pins */
	init_config();

	/* Go to first position of line1 */
	write_lcd(0x80, CMD_MODE);

	/* Infinite loop */
	while(1)
	{
		if (flag2 == 0)
		{
			/* To clear the contents of RCREG */
			while(!PIR1bits.RCIF);
			ch = RCREG;

			/* To enter a string */
			if (flag && ch != '#')
			{
				write_lcd(ch, DATA_MODE);
				arr[i] = ch;
				i++;
			}

			if (ch == '#')
			{
				flag = !flag;
				count++;
			}

			/* After entering two #, store remaining array spaces with spaces */
			if (count == 2)
			{
				flag2 = 1;

				for (i; i < 16; i++)
				{
					arr[i] = ' ';
				}
				arr[i] = '\0';
			}
		}

		if (flag2 == 1)
		{
			/* Get a key from MKP */
			key = scan_matrix_keypad();

			if (key != '0')
				prev = key;

			/* Function to scroll a message */
			scroll_message(arr);

			/* To print message on clcd */
			puts(LINE1_HOME, arr);
		}
	}
}
