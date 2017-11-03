#include "main.h"

char digits[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, DOT, BLANK};
extern char i, j , k , l, m, n, o , p;

// Function declaration seven segment display
void ssd_display(void)
{
    // Defining Seven segment display 
    SSD_PORT = digits[i] | digits[m];
    SSD3 = 1; SSD2 = 0; SSD1 = 0; SSD0 = 0;

    SSD_PORT = digits[j] | digits[n];
    SSD2 = 1; SSD3 = 0; SSD1 = 0; SSD0 = 0;

    SSD_PORT = digits[k] | digits[o];
    SSD1 = 1; SSD3 = 0; SSD2 = 0; SSD0 = 0;

    SSD_PORT = digits[l] | digits[p];
    SSD0 = 1; SSD3 = 0; SSD2 = 0; SSD1 = 0;
}
