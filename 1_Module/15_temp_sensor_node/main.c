#include "main.h"

/* Fucntion defintion Configure pins */
void init_config()
{
	init_CLCD_config();
	init_ADC_config();
}

/* Execution of program starts from here */
void main(void)
{
	unsigned short data;
	char message[] = "Temperature";

	/* Fucntion call Configure pins */
	init_config();

	/* To print a message */
	puts(LINE1_HOME, message);

	/* Infinite loop */
	while(1)
	{
		/* To store potentiometer value in data */
		data = adc();

		/* itoa display */
		itoa_display(data * 0.4887);
	}

}
