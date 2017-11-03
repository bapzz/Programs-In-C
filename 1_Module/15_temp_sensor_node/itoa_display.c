#include "main.h"

void itoa_display(unsigned short data)
{
	char array[5];
	int k;

	for (k = 0; k <= 3; k++)
	{
		/* Convert the result into ASCII */
		array[k] = data % 10 + '0';
		data = data / 10;
	}

	write_lcd(0xC0, CMD_MODE);
	for (k = 3; k >= 0; k--)
	{
		is_busy();

		/* Display the result on LCD */
		write_lcd(array[k], DATA_MODE);
	}
}
