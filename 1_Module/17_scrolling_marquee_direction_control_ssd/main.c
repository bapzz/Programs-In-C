#include "main.h"

void init_config(void)
{
	init_SSD_config();
	init_DKP_config();
}

void main(void)
{
	init_config();
	int flag;
	unsigned char key = 1;
	
	while(1)
	{
		ssd_display();
		key = scan_digital_keypad();

		if (key != 0)
		{
			flag = key;
		}
		if (flag == 1)
		{
			increment();
		}
		else if (flag == 2)
		{
			decrement();
		}
		else if (flag == 3)
		{
			;
		}
	}
}

