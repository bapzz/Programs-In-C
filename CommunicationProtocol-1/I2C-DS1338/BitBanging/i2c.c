#include "main.h"
#include "i2c.h"
#include "delay.h"

void init_i2c(void)
{	
	/* Write High on bus to satisfy bus idle condition */
	SCK = 1;
	SDA = 1;

	/* Make SDA pin output to start with, since this is the master */
	SDA_DIR = 0;
	/* Make SCK pin output */
	SCK_DIR = 0;
}

void i2c_start(void)
{
	SCK = 1;
	delay_us(HALF_BIT_DELAY);
	SDA = 0;
	delay_us(HALF_BIT_DELAY);
}

void i2c_rep_start(void)
{
	SCK = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 1;
	delay_us(HALF_BIT_DELAY / 2);

	SCK = 1;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 0;
	delay_us(HALF_BIT_DELAY / 2);
}

void i2c_stop(void)
{
	SCK = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SCK = 1;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 1;
	delay_us(HALF_BIT_DELAY / 2);
}

void i2c_send_ack(void)
{
	SCK = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SCK = 1;
	delay_us(HALF_BIT_DELAY);
}

void i2c_send_nack(void)
{
	SCK = 0;
	delay_us(HALF_BIT_DELAY / 2);
	SDA = 1;
	delay_us(HALF_BIT_DELAY / 2);
	SCK = 1;
	delay_us(HALF_BIT_DELAY);
}

bit i2c_write(unsigned char data)
{
	unsigned char bit_index;
	unsigned char ack;
	
	bit_index = 7;
	do
	{
		SCK = 0;
		delay_us(HALF_BIT_DELAY / 1);	
		/* Data is written at Low Level of SCK */
		SDA = (data >> bit_index) & 0x01;

		delay_us(HALF_BIT_DELAY / 2);
		SCK = 1;
		delay_us(HALF_BIT_DELAY);
	} while (bit_index--);
		
	/* Get ACK from slave */
	SCK = 0;
    SET_SDA_HIGH;
    delay_us(HALF_BIT_DELAY);
    SCK = 1;
    delay_us(HALF_BIT_DELAY);
	ack = SDA;
	SET_SDA_LOW;

	return (ack & 0x01);
}

unsigned char i2c_read(unsigned char ack)
{
	unsigned char bit_index;
	unsigned char rx_data = 0;

	SET_SDA_HIGH;

	bit_index = 7;
	do
	{
		SCK = 0;
		delay_us(HALF_BIT_DELAY);
		SCK = 1;
		delay_us(HALF_BIT_DELAY / 2);

		/* Data is read at High Level of SCK */
		rx_data = rx_data | (SDA << bit_index);
		delay_us(HALF_BIT_DELAY / 2);
	} while (bit_index--);

	SET_SDA_LOW;
 
    return rx_data;
}
