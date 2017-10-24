#include "header.h"
int zeros = 0, ones = 0;
int all_bits(int num)
{
	if (num == 1)
	{
		ones++;
		return 1;
	}
	for (int i = (sizeof(int) * 8) - 1 ; i > 0; i--)
	{
		if (num & (1 << i))
		{
			for (int j = i; j >= 0; j--)
			{
				if (num & (1 << j))
					ones++;
				else
					zeros++;
			}
			return 1;
		}
	}
}

int main(int argc, int *argv[])
{
	int num;
	printf("Enter the num :- ");
	scanf("%d", &num);

	int ret = all_bits(num);
	
	printf("zeros = %d, ones = %d\n", zeros, ones);
	
	return 0;
}
