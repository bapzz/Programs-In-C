#include "main.h"

void init_config()
{
	init_clcd_config();
}

void main()
{
	char message[] = "WELCOME BAPZZ";
	init_config();

	while(1)
	{
		puts(line1_home, message);
	}

}
