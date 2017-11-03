#include <xc.h>

/* This file should be used with PIC18F series controllers */

/* Configuration Word. Without setting this your system might not work */
#pragma config OSC = XT 	/* Oscillator Selection bits (External oscillator) */
#pragma config WDT = OFF  	/* Watchdog Timer disable bit (WDT disabled) */
#pragma config PWRT = OFF 	/* Power-up Timer disable bit (PWRT disabled) */
#pragma config BOREN = OFF 	/* Brown-out Reset disable bit (BOR disabled) */
#pragma config PBADEN = OFF     /* Analog PortB  Disable (PBADEN disable ) */
#pragma config LVP = OFF 	/* Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit */
#pragma config CPD = OFF 	/* Data EEPROM Memory Code Protection bit (Data EEPROM code protection off) */
