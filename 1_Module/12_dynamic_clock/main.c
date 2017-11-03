#include "main.h"

// To configure seven segment and timer 0
void init_config (void)
{
    init_ssd_config();
    init_TIMER0_config();
}

unsigned long decount;
unsigned char flag, key;
// Execution of program starts from here
void main(void)
{
    init_config();
    while(1)
    {
	/* To scan for a key pressed from DKP */
	(!flag) ? key = scan_digital_keypad() : key = 0;

	/* To avoid debouncing effect */
	(decount == 10000) ? decount = 0, flag = 0 : decount++;

	// Tiimer Delay 
	timer0_delay();

	// Function call for increementing
	increment();
    }
}

