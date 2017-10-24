#include "header.h"

int circular_shift_left(int num, int bits)
{
	int temp = (num >> (sizeof(int)*8 - bits)) & ((1 << bits) - 1);
	return ((num << bits) | (temp));
}

int main(int argc, int *argv[])
{
	int num, bits;
	printf("ENter the number :- ");
	scanf("%d", &num);
	printf("ENter the bits to be shifted left :- ");
	scanf("%d", &bits);
	print_bits(num);
	int ret = circular_shift_left(num, bits); 
	print_bits(ret);
	printf("new number :- %d\n", ret);

	return 0;
}
