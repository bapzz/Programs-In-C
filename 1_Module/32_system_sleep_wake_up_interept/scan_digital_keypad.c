#include "main.h"

unsigned char scan_digital_keypad(void)
{
	if(!SWITCH15)
		return 1;
	return 0;
}
