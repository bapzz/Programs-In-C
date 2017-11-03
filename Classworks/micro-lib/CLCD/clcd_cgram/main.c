/* 
 * Name   : clcd cgram display 
 * Author : Emertxe Information Technologies. 
 * Date   : 10/03/2016
 */

#include "main.h"

/*-------------------------- Define Custom Characters ------------------------------------------------*/
const unsigned char character_1[8]   = { 0x0E, 0x1B, 0x1B, 0x1F, 0x1B, 0x1B, 0x1B, 0x00 };    /* 'A'  */
const unsigned char character_2[8]   = { 0x18, 0x18, 0x18, 0x18, 0x18, 0x1F, 0x1F, 0x00 };    /* 'L'  */
const unsigned char character_3[8]   = { 0x1F, 0x1F, 0x04, 0x04, 0x04, 0x1F, 0x1F, 0x00 };    /* 'I'  */
const unsigned char character_4[8]   = { 0x0E, 0x19, 0x1D, 0x0E, 0x07, 0x1B, 0xE0, 0x00 };    /* 'S'  */
const unsigned char character_5[8]   = { 0x11, 0x11, 0x11, 0x15, 0x15, 0x15, 0x0A, 0x00 };    /* 'W'  */
const unsigned char character_6[8]   = { 0x1F, 0x18, 0x18, 0x1E, 0x18, 0x18, 0x1F, 0x00 };    /* 'E'  */
/*--------------------------------------------------------------------------------------------*/

/*-------------------------- Build Custom Characters -----------------------------------------*/
void CG_RAM(void)
{
	clcd_cgram(0, character_1);  		/* Build Character at position 0  */ 
	clcd_cgram(1, character_2);   		/* Build Character at position 1  */ 
	clcd_cgram(2, character_3);   		/* Build Character at position 2  */ 
	clcd_cgram(3, character_4);   		/* Build Character at position 3  */ 
	clcd_cgram(4, character_5);   		/* Build Character at position 4  */ 
	clcd_cgram(5, character_6);   		/* Build Character at position 5  */  
}
/*--------------------------------------------------------------------------------------------*/

static void init_config(void)
{
	init_clcd();
	CG_RAM();
}

int main(void)
{
	init_config();

	/* Goto first line of clcd */
	clcd_print("  Emertxe India ", LINE1(0));
#if 1
	/* Goto second line of clcd */
	write(0xC0, INSTRUCTION_COMMAND);
	write(' ', DATA_COMMAND);
	write(0x00, DATA_COMMAND);   
	write(0x01, DATA_COMMAND);   
	write(0x01, DATA_COMMAND);   
	write(' ', DATA_COMMAND);
	write(0x02, DATA_COMMAND);   
	write(0x03, DATA_COMMAND);   
	write(' ', DATA_COMMAND);
	write(0x04, DATA_COMMAND);   
	write(0x05, DATA_COMMAND);   
	write(0x01, DATA_COMMAND);   
	write(' ', DATA_COMMAND);
	write('-', DATA_COMMAND);
	write('_', DATA_COMMAND);
	write('-', DATA_COMMAND);
	write('!', DATA_COMMAND);
#endif
	while (1)
	{
		;
	}

	return 0;
}
