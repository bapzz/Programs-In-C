#include "main.h"

void init_CCP_config(void)
{
	// config CCP1CON reg.
	
	//CCP1M3:CCP1M0: CCP1 Module Mode select bits
	//SElect PWM mode
	CCP1M3 = 1;
	CCP1M2 = 1;
	CCP1M1 = 0; // Don't care
	CCP1M0 = 0; // Don't care

	// To take care of decimal part
	DC1B1 = 0;
	DC1B0 = 0;

	// Load CCPR1L with 50% duty cycle value
	CCPR1L = 62;
	//CCPR1L = 124;

	// COnfig CCP pin as an output pin
	TRISCbits.TRISC2 = 0;
}
