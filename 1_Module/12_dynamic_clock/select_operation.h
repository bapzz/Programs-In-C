#ifndef SELECT_OPERATION_H
#define SELECT_OPERATION_H

#define SW15 PORTCbits.RC0
#define SW16 PORTCbits.RC1
#define SW17 PORTCbits.RC2
#define SW18 PORTCbits.RC3

#define LED1 PORTBbits.RB1

#define PRESS 0
unsigned char scan_digital_keypad(void);

#endif
