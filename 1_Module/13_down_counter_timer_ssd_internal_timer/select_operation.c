#include "main.h"

extern unsigned char flag;
extern unsigned long int decount;
unsigned char scan_digital_keypad(void)
{
    if (SW15 == PRESS || SW16 == PRESS)
	return (SW15 == PRESS) ? flag = 1, decount = 0, 1  : (SW16 == PRESS) ? flag = 1, decount = 0, 2 : 0;
    else
	return (SW17 == PRESS) ? flag = 1, decount = 0, 3  : (SW18 == PRESS) ? flag = 1, decount = 0, 4 : 0;
}
