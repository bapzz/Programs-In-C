#include "main.h"

unsigned char scan_digital_keypad(void)
{
	  if(!SWITCH15)
	  {
		 key1 = 1;
		 return 1;
	  }
	  return 0;
}
