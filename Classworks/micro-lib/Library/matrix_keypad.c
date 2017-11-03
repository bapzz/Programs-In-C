/*
 * Name   : Matrix switches configuration file 
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "matrix_keypad.h"

void init_matrix_keypad(void)
{
	/* PORTB pull-ups are enabled by individual port latch values*/
	RBPU = 0;							 

	/* Setting the direction of Rows abd Columns */
	TRISB = 0x1E;

	/* Clear all pin of PORTB to ZERO */
	MATRIX_KEYPAD_PORT = MATRIX_KEYPAD_PORT & 0x00;
}

unsigned char scan_keypad(void)
{
	unsigned char row, col, bounce_delay;

	for (row = 0; row < NO_OF_ROWS; row++)
	{
		MATRIX_KEYPAD_PORT = (MATRIX_KEYPAD_PORT | 0xE0) & ~(0x20 << row); 

		for (col = 0; col < NO_OF_COLS; col++)
		{
			if (!(MATRIX_KEYPAD_PORT & 0x02 << col))
			{
				for (bounce_delay = 255; bounce_delay--;);
				return (row * NO_OF_COLS) + col;
			}
		}
	}

	return 0;
}

