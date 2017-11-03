#include "main.h"

unsigned char scan_digital_keypad(void)
{
	//if switch 15 is press
	
	if (!SWITCH2)
		return 1;
	if (!SWITCH3)
		return 2;
	if (!SWITCH4)
		return 3;
	if (!SWITCH5)
		return 4;
	if (!SWITCH6)
		return 5;
	if (!SWITCH7)
		return 6;


	//if non of the switch is press
	return key;

}
