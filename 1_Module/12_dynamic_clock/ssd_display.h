#ifndef SSD_DISPLAY_H
#define SSD_DISPLAY_H

#define ZERO	0xE7
#define ONE	0x21
#define TWO	0xCB
#define THREE	0x6B
#define FOUR	0x2D
#define FIVE	0x6E
#define SIX	0xEE
#define SEVEN	0x23
#define EIGHT	0xEF
#define NINE	0x6F
#define DOT	0x10
#define BLANK	0x00

#define SSD_PORT PORTD
#define SSD0 PORTAbits.RA0
#define SSD1 PORTAbits.RA1
#define SSD2 PORTAbits.RA2
#define SSD3 PORTAbits.RA3

void ssd_display(void);

#endif
