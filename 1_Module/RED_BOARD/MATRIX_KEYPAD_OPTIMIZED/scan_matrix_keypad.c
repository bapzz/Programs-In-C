#include "main.h"

unsigned char scan_matrix_keypad(void)
{
	unsigned short i;
	/* Scan for the key oress in first row */
	ROW1 = 0; ROW2 = 1; ROW3 = 1;
	if (COL1 == 0 && COL2 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '1';
	}
	else if (COL2 == 0 && COL1 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '2';
	}
	else if (COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '3';
	}
	else if (COL4== 0 && COL1 == 1 && COL2 == 1 && COL3 == 1)
	{
		for (i = 0; i < 400; i++);
		return '4';
	}
	
	/* Scan for the key oress in first row */
	ROW2 = 0; ROW1 = 1; ROW3 = 1;
	if (COL1 == 0 && COL2 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '5';
	}
	else if (COL2 == 0 && COL1 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '6';
	}
	else if (COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return '7';
	}
	else if (COL4== 0 && COL1 == 1 && COL2 == 1 && COL3 == 1)
	{
		for (i = 0; i < 400; i++);
		return '8';
	}
	
	/* Scan for the key oress in first row */
	ROW3 = 0; ROW1 = 1; ROW2 = 1;
	if (COL1 == 0 && COL2 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return 'A';
	}
	else if (COL2 == 0 && COL1 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return 'B';
	}
	else if (COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 400; i++);
		return 'C';
	}
	else if (COL4== 0 && COL1 == 1 && COL2 == 1 && COL3 == 1)
	{
		for (i = 0; i < 400; i++);
		return 'D';
	}

	return 0;
}
