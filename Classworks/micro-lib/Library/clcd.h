#ifndef CLCD_H
#define CLCD_H

#include "config.h"

#define CLCD_PORT						PORTD
#define CLCD_RW							PORTCbits.RC0
#define CLCD_RS							PORTCbits.RC1
#define CLCD_EN							PORTCbits.RC2


#define LINE1(x)						(0x80 + (x))
#define LINE2(x)						(0xC0 + (x))

#define	STABILIZE_LCD						clcd_write(0x33, INSTRUCTION_COMMAND);
#define	CLCD_4BITS_2LINE					clcd_write(0x28, INSTRUCTION_COMMAND);
#define	CLCD_8BITS_2LINE					clcd_write(0x38, INSTRUCTION_COMMAND);
#define CURSOR_HOME						clcd_write(0x02, INSTRUCTION_COMMAND);
#define DISP_ON_AND_CURSOR_OFF					clcd_write(0x0C, INSTRUCTION_COMMAND);
#define CLEAR_DISP_SCREEN					clcd_write(0x01, INSTRUCTION_COMMAND);
#define LEFT_SHIFT						clcd_write(0x18, INSTRUCTION_COMMAND);
#define RIGHT_SHIFT						clcd_write(0x1C, INSTRUCTION_COMMAND);

#define HI							1
#define LO							0

#define DATA_COMMAND						1
#define INSTRUCTION_COMMAND					0

void write(unsigned char bit_values, unsigned char control_bit);
void clcd_print(const unsigned char *data, unsigned char addr);
void clcd_putch(const unsigned char data, unsigned char addr);
void init_clcd(void);

#endif
