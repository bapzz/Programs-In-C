#include "i2c.h"

void init_i2c(void)
{
	/* Set SCL and SDA pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;

	/* Slew reate disable */
	SSPSTAT |= 0x80;

	/* Set I2C master mode */
	SSPCON1 = 0x28;


	/* Disable slew rate control  worked also with '0' */
	SMP = 1;

	/* Use I2C levels, worked also with '0' */
	CKE = 0;

	/* Clear SSPIF interrupt flag */
	SSPIF = 0;

	/* Enable SSPIE interrupt */
	SSPIE = 1;

	/* Set I2C speed 100 kHz */
	SSPADD = 0x31;
}

void i2c_start(void)
{
	SEN = 1;
	while (SEN);
}

void i2c_stop(void)
{
	PEN = 1;
	while (PEN);
}

void i2c_restart(void)
{
	RSEN = 1;
	while (RSEN);
}

void i2c_wait(void)
{
	while ((SSPCON2 & 0x1F ) || ( SSPSTAT & 0x04 ) );
}

void i2c_ack(void)
{
	ACKDT = 0;       
	ACKEN = 1;     
	while(ACKEN);   
}

void i2c_nak(void)
{
	ACKDT = 1;     
	ACKEN = 1;     
	while(ACKEN); 
}

unsigned char i2c_read(void)
{
	unsigned char data;

	RCEN = 1;
	while (!BF);
	data = SSPBUF;
	i2c_wait();

	return data;
}

void i2c_write(unsigned char data)
{
	SSPBUF = data;
	while (!BF);
	i2c_wait();
}
