#include "main.h"
#include "matrix_keypad.h"
#include "can.h"
#include "clcd.h"

/* delay 1ms function */
void delay_ms(unsigned short ms)
{
	unsigned short i, j;

	for (i = 0; i < ms; i++)
	{
		for (j = 500; j--; );
	}
}

void init_config(void)
{
	/* Initialize Matrix Keypad */
	init_matrix_keypad();

	/* Initialize CLCD module */
	init_clcd();

	/* Initialize CAN module */
	init_can();

	/* Set buzzer as output */
	TRISE0 = 0;
	BUZZER = 0;

	clcd_print("TEST CAN BUS", LINE1(2));
}

void can_demo(void)
{
	unsigned char key;

	key = read_switches(1);

	if (key == MK_SW3)
	{
		clcd_print("Tx DATA : --> ", LINE2(0));
		can_transmit();
	}

	if (can_receive())
	{
		clcd_print("Rx DATA : <--", LINE2(0));
		clcd_putch(can_payload[D3], LINE2(14));

		/* ON Sound */
		BUZZER = 1;
		delay_ms(500);
		BUZZER = 0;
	}
}

void main(void)
{    
	init_config();

	while (1)
	{
		can_demo();	
	}
}
