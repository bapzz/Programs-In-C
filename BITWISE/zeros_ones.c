#include "header.h"

int zero = 0, one = 0;

int zeros_ones(int num)
{
	for (int i = 0; i < sizeof(int) * 8; i++)
	{
		if (num & (1 << i))
			one++;
		else
			zero++;
	}
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);

	zeros_ones(num);
	printf("Zeros = %d, Ones = %d\n", zero, one);


}
