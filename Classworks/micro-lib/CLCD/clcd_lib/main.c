/* 
 * Name   : clcd display 
 * Author : Emertxe Information Technologies. 
 * Date   : 10/03/2016
 */

#include "main.h"

static void init_config(void)
{
	init_clcd();
}

void main(void)
{
	init_config();

	clcd_print("Test", LINE1(0)); 
	clcd_print("Hello Emertxe", LINE2(0));

	while (1)
	{
		;
	}
}
