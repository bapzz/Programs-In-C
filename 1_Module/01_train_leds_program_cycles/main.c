#include "main.h"

void init_config(void)
{
	init_LED_config();
}

void main(void)
{
	//configuring init
	init_config();
	//decalaring an delay variable
	int delay = DELY;
       	int flag = 0;
	
	while(1)
	{
		if (!delay--)
		{
			delay = DELY;
			
			if(state_flag == 0)
				train(); //train Right - Left  
			else
				train_reverse(); //train L-R
		}
	}	
}

