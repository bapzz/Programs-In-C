
#include "main.h"

void i2c_fail(unsigned char status)
{
	SSPCON2bits.PEN = 1;
	WAIT_MSSP;
	PORTB = status;
	while(1);
}

void write_external_eeprom(unsigned char address, unsigned char data)
{
	start;
	send_info(control_in);
	ack(0b00000001);
	send_info(address);
	ack(0b00000011);
	send_info(data);
	ack(0b00000111);
	stop;
}

unsigned char read_external_eeprom(unsigned char address)
{
	start;
	send_info(control_in);
	ack(0b01001111);
	send_info(address);
	ack(0b00011111);
	restart;
	send_info(control_out);
	ack(0b00111111);

	//change to recieve mode
	SSPCON2bits.RCEN = 1;
	WAIT_MSSP;

	nack;
	stop;

	return SSPBUF;
}
