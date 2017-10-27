#include "main.h"

void init_config()
{
	init_clcd_config();
	init_MKP_config();
}

void main()
{
	unsigned char prev, key;
	init_config();

	while(1)
	{
		key = scan_matrix_keypad();

		if (key != '0')
		{
			prev = key;
		}
		putchar(LINE1_HOME, prev);
	}

}
