#include "main.h"

void init_ADC_config(void)
{
	/* Config RAS pin as input pin */
	PORTEbits.RE1 = 1;

	/* Config ADCON2 ADCON1 ADCON0 */
	ADCON0 = 0X19;
	ADCON1 = 0X08;
	ADCON2 = 0X92;
}
