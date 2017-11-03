#include "main.h"

unsigned char scan_matrix_keypad(void)
{
	int i;
	// Scan for the key press in first row
	ROW1 = 0; ROW2 = 1; ROW3 = 1;
	if (COL1 == 0 && COL2 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '1';
	}
	else if (COL1 == 1 && COL2 == 0 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '2';
	}
	else if (COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '3';
	}
	else if (COL4 == 0 && COL1 == 1 && COL3 == 1 && COL2 == 1)
	{
		for (i = 0; i < 500; i++);
		return '4';
	}

	// Scan for the key press in second row
	ROW1 = 1; ROW2 = 0; ROW3 = 1;
	if(COL1 == 0 && COL3 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '5';
	}
	else if(COL2 == 0 && COL1 == 1 && COL3 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '6';
	}
	else if(COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return '7';
	}
	else if(COL4 == 0 && COL2 == 1 && COL3 == 1 && COL1 == 1)
	{
		for (i = 0; i < 500; i++);
		return '8';
	}

	// Scan for the key press in third row
	ROW1 = 1; ROW2 = 1; ROW3 = 0;


	if(COL2 == 1 && COL3 == 1 && COL4 == 1 && COL1 == 0)
	{
		for (i = 0; i < 500; i++);
		return '9';
	}
	else if(COL2 == 0 && COL3 == 1 && COL4 == 1 && COL1 == 1)
	{
		for (i = 0; i < 500; i++);
		return 'A';
	}
	else if(COL3 == 0 && COL1 == 1 && COL2 == 1 && COL4 == 1)
	{
		for (i = 0; i < 500; i++);
		return 'B';
	}
	else if(COL4 == 0 && COL1 == 1 && COL2 == 1 && COL3 == 1)
	{
		for (i = 0; i < 500; i++);
		return 'C';
	}
	return '0';
}
