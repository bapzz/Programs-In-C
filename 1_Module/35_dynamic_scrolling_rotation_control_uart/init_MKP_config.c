#include "main.h"

void init_MKP_config(void)
{
    // Config RB7, RB6, RB5 as an output pins
    // Config RB4, RB3, RG2, RB1, as an input pins

    // Note: Dont modify the LSB
    TRISB = (TRISB & 0x01) | 0x1E;

    // Enable internal pull-ups for the PORTB
    RBPU = 0;

    // Make all the PORTB as an digital port
    ADCON1 = 0x0E;
}
