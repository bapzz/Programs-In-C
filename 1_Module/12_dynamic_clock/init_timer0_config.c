#include "main.h"

void init_TIMER0_config(void)
{
    T0CON = 0xC7;
    /* Timer 0 interrupt flag is zero */
    TMR0IF = 0;
}
