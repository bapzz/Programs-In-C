#ifndef MATRIX_KEYPAD_H
#define MATRIX_KEYPAD_H

/* Refer pic_specific.h for port specific definations */

#define MAX_ROW			3
#define MAX_COL			4

#define STATE_CHANGE	1
#define LEVEL_CHANGE	0

#define MK_SW1			0
#define MK_SW2			1
#define MK_SW3			2
#define MK_SW4			3
#define MK_SW5			4
#define MK_SW6			5
#define MK_SW7			6
#define MK_SW8			7
#define MK_SW9			8
#define MK_SW10			9
#define MK_SW11			10
#define MK_SW12			11

#define ALL_RELEASED	0xFF

void init_matrix_keypad(void);
unsigned char scan_key(void);
unsigned char read_switches(unsigned char detection_type);

#endif
