#include "header.h"

int parity_check(int num)
{
	int count = 0;
	for(int i = 0; i < sizeof(int); i++)
	{
		if (num & (1 << i))
			count++;
	}
	return count%2;
}

int main(int argc, int *argv[])
{
	int num;
	printf("Enter the number :- ");
	scanf("%d", &num);

	int ret = parity_check(num);
	
	if (!ret)
		printf("Even Parity\n");
	else
		printf("Odd Parity\n");

	return 0;
}
