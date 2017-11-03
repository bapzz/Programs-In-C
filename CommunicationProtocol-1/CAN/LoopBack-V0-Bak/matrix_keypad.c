#include "pic_specific.h"
#include "matrix_keypad.h"

void init_matrix_keypad(void)
{
	/* Config PORTB as digital */
	ADCON1 = 0x0E;

	/* Set Columns (RB7 - RB5) as Inputs and Rows (RB4 - RB1) as Outputs */
	TRISB = (TRISB & 0xE1) | 0xE0;

	/* Set PORTB input as pull up for columns */
	RBPU = 0;

	MATRIX_KEY_PORT = MATRIX_KEY_PORT | 0x1E;
}

unsigned char scan_key(void)
{
	unsigned char row, col;

	for (row = 0; row < MAX_ROW; row++)
	{
		MATRIX_KEY_PORT = (MATRIX_KEY_PORT | 0x1E) & ~(0x02 << row); 

		for (col = 0; col < MAX_COL; col++)
		{
			if (!(MATRIX_KEY_PORT & (0x20 << col)))
			{
				return (row * MAX_COL) + col;
			}
		}
	}

	return 0xFF;
}

unsigned char read_switches(unsigned char detection_type)
{
	static unsigned char pres_key;
	static unsigned char prev_key;

	if (detection_type == STATE_CHANGE)
	{
		prev_key = pres_key;
		pres_key = scan_key();

		if (prev_key != pres_key)
		{
			return pres_key;
		}
	}
	else if (detection_type == LEVEL_CHANGE)
	{
		return scan_key();
	}

	return 0xFF;
}
