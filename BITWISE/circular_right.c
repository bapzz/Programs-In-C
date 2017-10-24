#include "header.h"

int circular_shift_right(int num, int bits)
{
	//int temp = num & ((1 << bits) -1);
	return ((num >> bits) | ((num & ((1 << bits) -1))<< (sizeof(int)*8 - bits)));
}

int main(int argc, int *argv[])
{
	int num, bits;
	printf("ENter the number :- ");
	scanf("%d", &num);
	printf("ENter the bits to be shifted right :- ");
	scanf("%d", &bits);
	print_bits(num);
	int ret = circular_shift_right(num, bits); 
	print_bits(ret);
	printf("new number :- %d\n", ret);

	return 0;
}
