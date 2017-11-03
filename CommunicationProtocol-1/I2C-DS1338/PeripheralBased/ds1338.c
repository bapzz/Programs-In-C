#include "main.h"
#include "ds1338.h"
#include "i2c.h"

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

void init_ds1338(void)
{
	unsigned char dummy;

	/* Reseting the CH bit of the RTC to Start the Clock */
	dummy = read_ds1338(SEC_ADDR);
	write_ds1338(SEC_ADDR, dummy & 0x7F); 
	/* Seting 12 Hr Format */
	dummy = read_ds1338(HOUR_ADDR);
	write_ds1338(HOUR_ADDR, dummy | 0x40); 

	/* 
	 * Control Register of DS1338
	 * Bit 7 - OUT
	 * Bit 6 - 0
	 * Bit 5 - OSF
	 * Bit 4 - SQWE
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1
	 * Bit 0 - RS0
	 * 
	 * Seting RS0 and RS1 as 11 to achive SQW out at 32.768 KHz
	 */ 
	write_ds1338(CNTL_ADDR, 0x93); 
}

void write_ds1338(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
}

unsigned char read_ds1338(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(0xD0);
	i2c_write(address);
	i2c_rep_start();
	i2c_write(0xD1);
	data = i2c_read(0x00);
	i2c_stop();

	return(data);
}
