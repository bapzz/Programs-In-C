#include "main.h"
#include "i2c.h"

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C master mode */
	SSPCON = 0x38;
	SSPCON2 = 0x00;

	SSPADD = 0x30;
	/* Use I2C levels, worked also with '0' */
	CKE = 1;
	/* Disable slew rate control  worked also with '0' */
	SMP = 1;
	/* Clear SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear bus collision flag */
	BCLIF = 0;
}

void i2c_wait_for_idle(void)
{
	while ((SSPCON2 & 0x1F ) | R_nW)
	{
		; /* wait for idle and not writing */
	}
}

void i2c_start(void)
{
	i2c_wait_for_idle();
	SEN = 1;
}

void i2c_rep_start(void)
{
	i2c_wait_for_idle();
	RSEN = 1;
}

void i2c_stop(void)
{
	i2c_wait_for_idle();
	PEN = 1;
}

int i2c_read(unsigned char ack)
{
	unsigned char i2c_read_data;

	i2c_wait_for_idle();

	RCEN = 1;

	i2c_wait_for_idle();

	i2c_read_data = SSPBUF;

	i2c_wait_for_idle();

	if (ack)
	{
		ACKDT = 0;
	}
	else
	{
		ACKDT = 1;
	}
	/* send acknowledge sequence */
	ACKEN = 1;

	return(i2c_read_data);
}

unsigned char i2c_write(unsigned char i2c_write_data)
{
	i2c_wait_for_idle();
	SSPBUF = i2c_write_data;
	/* Function returns '1' if transmission is acknowledged */
	return (!ACKSTAT);
}
