#include "main.h"
#include "isr.h"

char received_data;

void interrupt isr(void)
{
	static unsigned char offset;

	if (RCIF)
	{
		received_data = RCREG;

		RCIF = 0;
	}
}
