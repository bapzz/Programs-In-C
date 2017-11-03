#include "main.h"
#include "spi.h"

#ifndef BIT_BANGING
void init_spi(void)
{
	TRISC5 = 0;
	TRISC4 = 1;
	TRISC3 = 0;
	TRISC2 = 0;

	SSPSTAT = 0x40;
	SSPEN = 1;
	SSPIE = 0;
	PEIE = 1;

	DISABLE_CHIP_SELECT;
}

unsigned char spi_rw(char byte)
{
	SSPBUF = byte;
	do 
	{
	}
	while(!BF);

	return (SSPBUF);
}
#else
void init_spi(void)
{
	TRISC5 = 1;
	TRISC4 = 0;
	TRISC3 = 0;
	TRISC2 = 0;

	DISABLE_CHIP_SELECT;
}

/* Bit Banging */
unsigned char spi_rw(unsigned char data)
{
	unsigned short wait;
	signed char offset;
	
#if 0
	/* Need to initilized by 8 since the offset would get decremented by 1 in comparision */
	for (offset = 8; offset--; )
#endif
	
	offset = 8;
	do
	{
		SPI_SCK = LO;
		/* Transferring MSB to Slave*/
		SPI_MOSI = data >> 7;
		SPI_SCK = HI;
		/* Accepting the Slave data in LSB */
		data = (data << 1) | SPI_MISO;
	} while (offset--);

	for (wait = 100; wait--; );

	return data;
}
#endif
