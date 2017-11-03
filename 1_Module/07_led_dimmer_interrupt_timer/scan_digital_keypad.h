#ifndef SCAN_DIGITAL_KEYPAD_H
#define SCAN_DIGITAL_KEYPAD_H

#define SWITCH15 PORTCbits.RC0
#define SWITCH16 PORTCbits.RC1

unsigned char scan_digital_keypad(void);

#endif
