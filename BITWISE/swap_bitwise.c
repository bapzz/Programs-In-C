#include "header.h"

void swap_bitwise(int *a, int *b)
{
	*a ^= *b;
	*b ^= *a;
	*a ^= *b;
}

int main()
{
	int num1, num2;
	printf("ENter Two Numbers ;- ");
	scanf("%d%d", &num1, &num2);
	printf("Before swap :- num1 = %d, num2 = %d\n", num1, num2);

	swap_bitwise(&num1, &num2);
	printf("After swap :- num1 = %d, num2 = %d\n", num1, num2);

	return 0;
}
