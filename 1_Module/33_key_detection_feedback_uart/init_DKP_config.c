#include "main.h"

void init_DKP_config(void)
{
    /* Configure TRISC Reg */
    /* RC0, RC1, RC2, RC3 configure as input */
    /* Keep upper nibble unaltered */
    TRISC = TRISC | 0x0F;
}
