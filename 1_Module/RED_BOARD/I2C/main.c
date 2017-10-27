
#include "main.h"

void init_config(void)
{
	init_i2c_config ();
	init_clcd_config ();
}

void main(void)
{
	unsigned char ch;
	init_config();

	write_external_eeprom(0x05, 'P');
	delay(5);

	ch = read_external_eeprom(0x05);
	putchar(0x80, ch);

	while(1);
}

