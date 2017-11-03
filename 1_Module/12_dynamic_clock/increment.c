#include "main.h"

char i, j, k, l, m, n, o, p;
unsigned short count;
extern char key;

/* Function definition for increment */
void increment(void)
{
    static char prev = 0, flag = 0, pos = 0;

    // To display
    ssd_display();

    // To give the delay, using timer 
    if (count == 76)
    {
	m = 11;	n = 11;	o = 11;	p = 11;
	count = 0;

	if (prev == 4)
	    i++;
    } 

    /* If flag not set then it enters switch case */
    if (!flag)
    {
	switch(key)
	{
	    /* To increement the clock */
	    case 1:
		if(pos == 0)
		{
		    i++;
		    (i == 10) ? i = 0 : 0;
		}
		if(pos == 1)
		{
		    j++;
		    (j == 6) ? j = 0 : 0;
		}
		if(pos == 2)
		{
		    k++;
		    (k == 10) ? k = 0 : 0;
		}
		if(pos == 3)
		{
		    l++;
		    (l == 6) ? l = 0 : 0;
		}
		break;

		/* To decreement the clock */
	    case 2:
		if(pos == 0)
		{
		    i--;
		    (i > 10) ? i = 9 : 0;
		}
		if(pos == 1)
		{
		    j--;
		    (j > 6) ? j = 5 : 0;
		}
		if(pos == 2)
		{
		    k--;
		    (k > 10) ? k = 9 : 0;
		}
		if(pos == 3)
		{
		    l--;
		    (l > 6) ? l = 5 : 0;
		}
		break;

		/* To move the cursor */
	    case 3:
		if (pos > 2)
		    pos = 0;
		else
		    pos++;

		prev = key;

		break;
	}
    }

    /* To indicate the cursor by blinking dot */
    if (!flag && count == 36)
    {
	if (pos == 0)
	{
	    m = 10; n = 11; o = 11; p = 11;
	}
	if (pos == 1)
	{
	    m = 11; n = 10; o = 11; p = 11;
	}
	if (pos == 2)
	{
	    m = 11; n = 11; o = 10; p = 11;
	}
	if (pos == 3)
	{
	    m = 11; n = 11; o = 11; p = 10;
	}
    }

    /* To start and stop the clock, set the flag*/
    if (key == 4)
    {
	if (flag == 0)
	{
	    prev = key; flag = 1;
	}
	else
	{
	    prev = 0; flag = 0; pos = 0;
	}
    }

    if (key == 4 || prev == 4)
    {
	// To ON and OFF dot every half second
	if (count == 38)
	    o = 10;

	// To increment the values
	if (i == 10)
	{
	    i = 0;
	    j++;

	    if (j == 6) 
	    {
		j = 0;
		k++;

		if (k == 10)
		{
		    k = 0;
		    l++;

		    if (l == 6)
		    {
			l = 0;
		    }
		}
	    }
	}
    }
}
