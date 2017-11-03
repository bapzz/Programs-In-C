#ifndef SCAN_DIGITAL_KEYPAD_H
#define SCAN_DIGITAL_KEYPAD_H

#define SWITCH2 PORTBbits.RB0
#define SWITCH3 PORTBbits.RB1
#define SWITCH4 PORTBbits.RB2
#define SWITCH5 PORTBbits.RB3
#define SWITCH6 PORTBbits.RB4
#define SWITCH7 PORTBbits.RB5

unsigned char scan_digital_keypad(void);

#endif
