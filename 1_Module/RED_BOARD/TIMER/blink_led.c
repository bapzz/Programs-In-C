#include "main.h"

unsigned short count;

void blink_led (void) {
	if (count == 76) {
		count = 0;
		LEDS = ~LEDS;
	}
}
