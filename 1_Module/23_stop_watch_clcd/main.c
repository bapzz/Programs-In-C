#include "main.h"

//config CLCD
void init_config()
{
	init_clcd_config();
	init_mkp_config();
}

void main()
{
	char sw[] = "SW-";
	char count[] = "0000000000";
	char msg[] = "lap: ";
	init_config();

	//loop for program cycle
	while(1)
	{
		puts(line1_home, sw);

		key = scan_matrix_keypad();

		if (key == '1')
		{
			counter_inc(count);	
			if (!strcmp(count,"9999999999"))
				strcpy(count,"0000000000");
		}
		else if (key == '2')
		{
			strcpy(*lap[itr],count);
			itr++;
			key = '1';
		}
		else if (key == '3')
		{
			puts(line2_home, strcat(msg,*lap[i]));
			i++;
		}
		puts(line1_home+3, count);
		delay(700);
	}

}
