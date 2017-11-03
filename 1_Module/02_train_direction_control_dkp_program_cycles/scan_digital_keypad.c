#include "main.h"

unsigned char scan_digital_keypad(void)
{
	//if switch 15 is press
	if (!SWITCH3)
		return 1;

	//if non of the switch is press
	return 0;

}
