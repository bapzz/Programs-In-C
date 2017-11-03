#include "ssd.h"

void init_ssd_control(void)
{
	/* Setting PORTD Control lines as output */
	TRISD = TRISD & 0x00;

	/* Setting SSD Enable lines as output */
	TRISA = TRISA & 0xF0;

	/* Switching OFF all the SSDs to start with */
	SSD_CONTROL_PORT = SSD_CONTROL_PORT & 0xF0;
}

void display(unsigned char *data)
{
	unsigned int delay;
	unsigned char digit;

	for (digit = 0; digit < 4; digit++)
	{
		/* Send data to PORTD */
		SSD_PORT = SSD_DATA(digit);  

		/* Select each port for control SSDs */
		SSD_CONTROL_PORT = (SSD_CONTROL_PORT & 0xF0) | 0x01 << digit; 
		for (delay = 0; delay < 2500; delay++);
	}

}
