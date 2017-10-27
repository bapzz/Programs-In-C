#include "main.h"

void led_blink(void)
{

#if 0
	//Toggle Bits
	for (int i = 0; i < 8; i++)
	{
		LEDS = 0xAA;
		delay(1000);
		LEDS = 0x55;
		delay(1000);
	}
#endif

#if 0
	//toggle nibbles
	for (int i = 0; i < 8; i++)
	{
		LEDS = 0xF0;
		delay(1000);
		LEDS = 0x0F;
		delay(1000);

	}
#endif

#if 1
	//LED Train
	for (int i = 0; i < 8; i++)
	{
		LEDS = ((0xFF) & (~0 << i));
		delay(100);
	}
	
	for (int i = 0; i < 8; i++)
	{
		LEDS = ~((0xFF) & (~0 << i));
		delay(100);
	}
	
#endif

#if 0
	//LED Train Reverse
	for (int i = 1; i <=8; i++)
	{
		LEDS = ((0xFF) & (~0 << i));
		delay(500);
	}
	for (int i = 7; i >= 0; i--)
	{
		LEDS = ~((0xFF) & (~0 << i));
		delay(500);
	}
	
#endif

#if 0
	//print 0 - 255
	for (int i = 0; i <= 255; i++)
	{
		LEDS = ~i;
		delay(1000);
	}
#endif

}
