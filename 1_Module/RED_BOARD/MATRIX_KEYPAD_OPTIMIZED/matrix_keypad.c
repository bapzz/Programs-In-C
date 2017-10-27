#include "main.h"

unsigned char scan_keypad(void)
{
	unsigned char row, col;

	for (row = 0; row < NO_OF_ROWS; row++)
	{
		MATRIX_KEYPAD_PORT = (MATRIX_KEYPAD_PORT | 0x07) & ~(0x01 << row);

		for (col = 0; col < NO_OF_ROWS; col++)
		{
			if (!(MATRIX_KEYPAD_PORT & 0x08 << col))
			{
				return (row * NO_OF_ROWS) + col;
			}
		}
	}

	return -1;
}
#if 0
void init_matrix_keypad(void)
{
	/* setting the row outputs to start with */
	MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT | 0x07;
	/* setting the direction of rows and coloums */
	TRISB = 0x38;
}
#endif
