#include "main.h"

void init_config()
{
	init_SSD_config();
	init_DKP_config();
	init_LED_config();
}

void main()
{
	init_config();
	char ch;
#if 0
	/* Reseting the EEPROM  */
	unsigned char *ptr = 0x00;
	while ((*ptr++) != 0xFF)
		write_internal_eeprom(*ptr,'0');
#else
	/* Reads the EEPROM and saves it */	
	if ((ch = read_internal_eeprom(0x00)) != '0')
	{
		LED1 = ON;
		i = read_internal_eeprom(0x00);
		j = read_internal_eeprom(0x01);
		k = read_internal_eeprom(0x02);
		l = read_internal_eeprom(0x03);
	}
	else
	{
		LED2 = ON;
		i = 0, j = 0, k = 0, l = 0;
	}

	while(1)
	{
		ssd_display();
		if (!key_delay--)
		{
			key_delay = 700;
			key = scan_digital_keypad();
			/* writes the data to EEPROM */
			if (key == 1)
			{
				LED3 = ON;
				write_internal_eeprom(0x00,i);
				write_internal_eeprom(0x01,j);
				write_internal_eeprom(0x02,k);
				write_internal_eeprom(0x03,l);
			}
		}
		
		/* starts the count */
		if (!count--) 
		{
			count = 250000;
			increment();
		}
	}
#endif
}
