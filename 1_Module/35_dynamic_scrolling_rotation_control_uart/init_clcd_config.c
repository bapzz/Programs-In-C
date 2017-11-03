#include "main.h"

void init_CLCD_config(void)
{
	//config PORTD as output, for sending the data
	TRISD = 0;

	//CONFIG PORTC as outputport, for sending the control signals
	TRISC = TRISC & 0XF8;

	EIGHT_BIT_TWO_LINE_DISPLAY;
	delay(250);

	DISPLAY_ON_CURSOR_ON;
	delay(250);

	CLEAR_DISPLAY;
	delay(5);

	ENTRY_MODE;
	delay(5);
}
