
#include "main.h"

void init_i2c_config(void)
{
#if 0
	//config PORTB
	TRISB = 0;
	ADCON1 = 0x0E;
	LATB = 0;
#endif
	//config PORTC as bidirectional
	SDA = 1;
	SCL = 1;

	//configure MSSP module
	SSPSTAT = 0x80;
	SSPCON1 = 0x28;

	//calculated according to AAPADD = ((Fosc / bit - rate) / 4) - 1
	// Fosc = 20Mhz and bit - rate = 1Mhz
	SSPADD = 4;
}
