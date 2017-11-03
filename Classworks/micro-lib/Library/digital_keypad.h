#ifndef DIGITAL_KEYPAD_H
#define DIGITAL_KEYPAD_H

#include "config.h"

#define INPUT_PINS		0x0F
#define DEFAULT_INPUT_LEVEL	0x0F

#define DIRECTION_REGISTER	TRISC
#define PORT			PORTC

#define SET_INPUTS		DIRECTION_REGISTER |= INPUT_PINS
#define RESET_INPUTS		DIRECTION_REGISTER &= ~INPUT_PINS

#define DETECT_STATE		detection_type == 1
#define CONTINUOUS		detection_type == 0

#define STATE			1
#define LEVEL			0

/* Enable this if you want to read state transition in pull up config*/
/* Enable this if you want to read level transition in pull down config*/
#if 1 
#define SWITCH1			0x01
#define SWITCH2			0x02
#define SWITCH3			0x04
#define SWITCH4			0x08
/* Enable this if you want to read state transition in pull up config*/
#else 
#define SWITCH1			0x3E
#define SWITCH2			0x3D
#define SWITCH3			0x3B
#define SWITCH4			0x37
#endif

void init_digital_keypad(void);
unsigned char read_switches(unsigned char detection_type);

#endif
