#ifndef SSD_H
#define SSD_H

#include "config.h"

#define SSD_PORT			PORTD
#define SSD_CONTROL_PORT		PORTA
#define SSD_DATA(x)			(SSD_PORT & 0x00 | data[x])

#define ZERO				0xE7
#define ONE				0x21
#define TWO				0xCB
#define THREE				0x6B
#define FOUR				0x2D
#define FIVE			 	0x6E
#define SIX				0xEE
#define SEVEN				0x23
#define EIGHT				0xEF
#define NINE				0x6F
#define DOT				0x10
#define MINUS				0x08
#define BLANK				0x00	
#define MINUS_ONE			0x29

void init_ssd_control(void);
void display(unsigned char *data);

#endif
