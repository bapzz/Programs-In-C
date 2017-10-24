#include "header.h"

int all_bits(int num)
{
	int count = 0;
	if (num == 1)
		return 1;

	for (int i = (sizeof(int) * 8) - 1 ; i > 0; i--)
	{
		if (num & (1 << i))
		{
			for (int j = i; j >= 0; j--)
			{
				if (num & (1 << j))
					count++;
			}
			if (count == ++i)
				return 1;
			else
				return 0;
		}
	}
}

int main(int argc, int *argv[])
{
	int num;
	printf("Enter the num :- ");
	scanf("%d", &num);

	int ret = all_bits(num);
	
	if(ret)
		printf("all bits are one\n");
	else
		printf("all bits are mixed\n");
	
	return 0;
}
