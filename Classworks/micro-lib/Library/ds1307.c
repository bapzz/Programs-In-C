/*
 * Name   : Real-Time Clock (DS1307) configuration file 
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "ds1307.h"

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

void init_ds1307(void)
{
	unsigned char dummy;

	init_i2c();

	/* Reseting the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);
	write_ds1307(SEC_ADDR, dummy & 0x7F); 
	/* Seting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);
	write_ds1307(HOUR_ADDR, dummy | 0x40); 

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
	write_ds1307(CNTL_ADDR, 0x93); 
}

void write_ds1307(unsigned char address, unsigned char data)
{
	i2c_start();
	i2c_write(0xD0);
	i2c_write(address);
	i2c_write(data);
	i2c_stop();
}

unsigned char read_ds1307(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(0xD0);
	i2c_write(address);
	i2c_restart();
	i2c_write(0xD1);
	data = i2c_read();
	i2c_stop();

	return(data);
}
