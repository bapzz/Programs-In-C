#include "main.h"

extern unsigned char prev;
char i, temp;
/* Function definition for right scroll */
void scroll_right_message(char *ptr)
{
	/* To move 1 bit to the right */
	for (i = 15; i >= 0 && i < 16; i--)
	{
		if (i == 15)
		{
			temp = ptr[i];		// To store last bit to a temporary variable
		}

		// To store the last bit content to the first bit
		if (i == 0)
			ptr[i] = temp;
		else
			ptr[i] = ptr[i - 1];
	}
	delay(200);
}

/* Function definition for left scroll */
void scroll_left_message(char *ptr)
{
	/* To move 1 bit to the left */
	for (i = 0; i < 16; i++)
	{
		if (i == 0)
		{
			temp = ptr[i];		// To store first bit to a temporary variable
		}

		// To store the first bit content to the last bit
		if (i == 15)
			ptr[i] = temp;
		else
			ptr[i] = ptr[i + 1];
	}
	delay(200);
}

/* Function definition to scroll a message */
void scroll_message(char *ptr)
{
	if (prev == '1')
	{
		/* Function call for left scroll */
		scroll_left_message(ptr);
	}
	else if (prev == '4')
	{
		/* Function call for right scroll */
		scroll_right_message(ptr);
	}
}
