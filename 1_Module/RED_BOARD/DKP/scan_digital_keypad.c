#include "main.h"

unsigned char scan_digital_keypad(void)
{
	//if switch 15 is press
	if (!SWITCH15)
		return 1;
	//if switch 16 is press
	else if (!SWITCH16)
		return 2;
	//if switch 17 is press
	else if (!SWITCH17)
		return 3;
	//if switch 18 is press
	else if (!SWITCH18)
		return 4;
	//if non of the switch is press
	return 0;

}
