#include "main.h"

void init_config(void)
{
	init_uart_config();
	init_CLCD_config();
}

void main()
{
	unsigned char ch,flag=0;
	int i,j;

	init_config();

	// go to first position of line1

	write_lcd(0x80,CMD_MODE);

	while(1)
	{
		while(!PIR1bits.RCIF);
		ch = RCREG;

		/* To write on controller */	
		if (flag && ch!= '$')
			write_lcd(ch,DATA_MODE);

		if (ch == '$')
			flag = !flag;

	}

}

