#include "main.h"

char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
extern char i, j, k, l;

void ssd_display(void)
{
	SSD_PORT = digits[i];
	SSD3 = 1; SSD2 = 0; SSD1 = 0; SSD0 = 0;

	SSD_PORT = digits[j];
	SSD2 = 1; SSD3 = 0; SSD1 = 0; SSD0 = 0;

	SSD_PORT = digits[k];
	SSD1 = 1; SSD3 = 0; SSD2 = 0; SSD0 = 0;

	SSD_PORT = digits[l];
	SSD0 = 1; SSD3 = 0; SSD2 = 0; SSD1 = 0;
}
