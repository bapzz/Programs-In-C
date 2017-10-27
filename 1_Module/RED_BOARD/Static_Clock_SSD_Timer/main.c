#include "main.h"

void init_config(void)
{
	init_timer0_config();
	init_SSD_config();
}

void main(void)
{
	init_config();

	while(1)
	{
		increment();
	}
}

