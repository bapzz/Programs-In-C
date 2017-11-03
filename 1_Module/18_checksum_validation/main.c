#include "main.h"

void init_config()
{
	init_clcd_config();
	init_mkp_config();
}

void main()
{
	char message[] = "*** CHECKSUM ***";
	init_config();

	puts(line1_home, message);

	while(1)
	{
		/* To give the delay */
		if (!delay1--)
		{
			delay1 = 50;
			key = scan_matrix_keypad();
		}
		/* makes 1 and 0 on pressing of key */
		if (key == '1')
		{
			if( bits[0] == '0')
				bits[0] = '1';
			else
				bits[0] = '0';
		}
		else if (key == '2')
		{
			if( bits[1] == '0')
				bits[1] = '1';
			else
				bits[1] = '0';
		}
		else if (key == '3')
		{
			if( bits[2] == '0')
				bits[2] = '1';
			else
				bits[2] = '0';
		}
		else if (key == '4')
		{
			if( bits[3] == '0')
				bits[3] = '1';
			else
				bits[3] = '0';
		}
		else if (key == '5')
		{
			if( bits[4] == '0')
				bits[4] = '1';
			else
				bits[4] = '0';
		}
		else if (key == '6')
		{
			if( bits[5] == '0')
				bits[5] = '1';
			else
				bits[5] = '0';
		}
		else if (key == '7')
		{
			if( bits[6] == '0')
				bits[6] = '1';
			else
				bits[6] = '0';
		}
		else if (key == '8')
		{
			if( bits[7] == '0')
				bits[7] = '1';
			else
				bits[7] = '0';
		}
		/* checks for the no of 1 's for parity check */
		if (key == '9')
		{
			for(i = 0; i < 8; i++)
			{
				if( bits[i] == '1')
					parity+=1;
			}
			/* if even */
			if(!(parity%2))
			{
				bits[12] = '1';
				bits[14] = 'E';
				parity = 0;
			}
			else	/* if odd */
			{
				bits[12] = '0';
				bits[14] = 'O';
				parity = 0;
			}
		}
		i = 0;
		puts(line2_home, bits );
	}

}
