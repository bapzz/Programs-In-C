#include "main.h"

void init_ssd_config(void)
{
    // Config PORTD as an output
    TRISD = 0;

    // Config PORTA as an output
    TRISA = TRISA & 0xF0;
}
