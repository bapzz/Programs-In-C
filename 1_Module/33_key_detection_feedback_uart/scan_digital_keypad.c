#include "main.h"

unsigned char scan_digital_keypad(void)
{
	
	if(!SWITCH15)
		return 'A';
	if(!SWITCH16)
		return 'B';
	if(!SWITCH17)
		return 'C';
	if(!SWITCH18)
		return 'D';
		
	return 0xFF;
}
