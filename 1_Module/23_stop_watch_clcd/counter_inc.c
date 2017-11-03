#include "main.h"

void counter_inc(char *count)
{
		  count[9]++;
		  for(i = 9;i >= 0;i--)
		  {
					 if (count[i] >= ':')
					 {
								count[i-1]++;
								count[i] = '0';	
					 }
		  }
}
