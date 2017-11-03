/*
 * Name   : External EEPROM (ATMEL-24C04N) configuration file 
 * Author : Emertxe Information Technologies 
 * Date   : 10/03/2016
 */

#include "eeprom_24c04.h"

void init_eeprom(void)
{
	init_i2c();
}

void write_eeprom(unsigned char address, unsigned char data)
{
	unsigned int wait;

	i2c_start();
	i2c_write(WRITE_MODE);	/* Send address to write mode to eeprom */
	i2c_write(address);	/* Select address for write the data */
	i2c_write(data);	/* Write data to eeprom */
	i2c_stop();
	for (wait = 0; wait < 500; wait++);
}

unsigned char read_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();
	i2c_write(WRITE_MODE);	/* Send address to write mode to eeprom */
	i2c_write(address);	/* Select address for read the data */
	i2c_restart();		
	i2c_write(READ_MODE);	/* Send address to read mode to eeprom */
	data = i2c_read();
	i2c_stop();

	return(data);
}
