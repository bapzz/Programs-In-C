#ifndef SCAN_DIGITAL_KEYPAD_H
#define SCAN_DIGITAL_KEYPAD_H

#define SWITCH15 PORTCbits.RC0
#define SWITCH16 PORTCbits.RC1
#define SWITCH17 PORTCbits.RC2
#define SWITCH18 PORTCbits.RC3

unsigned char scan_digital_keypad();

#endif
