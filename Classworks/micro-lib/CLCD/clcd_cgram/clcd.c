#include "clcd.h"

void write(unsigned char bit_values, unsigned char control_bit)
{
	unsigned short wait;
	/* clcd 4bits mode */
#if 0

	CLCD_RS = control_bit;
	CLCD_PORT = (CLCD_PORT & 0x0F) | (bit_values & 0xF0);
	CLCD_EN = HI;
	CLCD_EN = LO;
	CLCD_PORT = (CLCD_PORT & 0x0F) | ((bit_values << 4) & 0xF0);
	CLCD_EN = HI;
	CLCD_EN = LO;
	for (wait = 500; wait--; );
#endif
	/* clcd 8bits mode */
	CLCD_PORT = bit_values;

	CLCD_RS = control_bit;
	CLCD_EN = LO;
	CLCD_EN = HI;
	for (wait = 500; wait--; );
	CLCD_EN = HI;
	CLCD_EN = LO;
	for (wait = 500; wait--; );
}

void clcd_print(const unsigned char *data, unsigned char addr)
{
	write(addr, INSTRUCTION_COMMAND);
	while (*data != '\0')
	{
		write(*data++, DATA_COMMAND);
	}
}

void clcd_putch(const unsigned char data, unsigned char addr)
{
	write(addr, INSTRUCTION_COMMAND);
	write(data, DATA_COMMAND);
}

void clcd_cgram(unsigned char loc, const unsigned char *p)
{
	unsigned char i;

	if (loc < 8)                        
	{
		write(0x40 + (loc * 8), INSTRUCTION_COMMAND);       
		for (i = 0; i < 8; i++)
		{
			write(p[i], DATA_COMMAND);
		}
	}    
}

void init_clcd(void)
{
	unsigned short wait;
	/* Set PortD and PortC as output port */
	TRISD = 0x00;
	TRISC = 0xF8;

	STABILIZE_LCD;
	CLCD_8BITS_2LINE;
	CURSOR_HOME;
	DISP_ON_AND_CURSOR_OFF;
	CLCD_CGRAM;
	CLEAR_DISP_SCREEN;
}
