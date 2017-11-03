#include "main.h"

void init_config()
{
	init_clcd_config();
}

void main()
{
	char message[] = "BISWAJEET SAHOO ";
	char temp;
	init_config();

	int i;

	while(1)
	{
		puts(line1_home, message);
		delay(1500);
		//saving the last value in temp	
		temp = message[15];
		//coping next value to prev one
		for (i = 16;i > 0; i--)
		{
			message[i] = message[i - 1];

		}
		//assigning temp to first
		message[0] = temp;
	}

}
