#include "main.h"
#include "25lc040.h"
#include "spi.h"
#include "delay.h"

static unsigned char dummy;

void eeprom_25lc040_byte_write(unsigned char memory_loc, unsigned char data)
{
	unsigned short wait;

	ENABLE_CHIP_SELECT;
	dummy = spi_rw(WRITE_ENABLE);
	DISABLE_CHIP_SELECT;

	for (wait = 100; wait--; );

	ENABLE_CHIP_SELECT;
	dummy = spi_rw(WRITE_INSTR);
	dummy = spi_rw(memory_loc);
	dummy = spi_rw(data);
	DISABLE_CHIP_SELECT;
	delay_ms(5);
}

/* Max 16 bytes can be written for 25LC040 */
void eeprom_25lc040_page_write(unsigned char memory_loc, unsigned char *data, unsigned char count)
{
	unsigned short wait;

	ENABLE_CHIP_SELECT;
	dummy = spi_rw(WRITE_ENABLE);
	DISABLE_CHIP_SELECT;

	for (wait = 100; wait--; );

	ENABLE_CHIP_SELECT;
	dummy = spi_rw(WRITE_INSTR);
	dummy = spi_rw(memory_loc);

	do
	{
		dummy = spi_rw(*data++);
	} while (--count);

	DISABLE_CHIP_SELECT;
	delay_ms(5);
}

unsigned char eeprom_25lc040_read(unsigned char memory_loc)
{
	char spi_received = 0;

	ENABLE_CHIP_SELECT;
	dummy = spi_rw(READ_INSTR);
	dummy = spi_rw(memory_loc);
	spi_received = spi_rw(0xFF);
	DISABLE_CHIP_SELECT;

	return (spi_received);
}
