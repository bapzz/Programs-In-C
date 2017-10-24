#include "header.h"

int set_nth_bit(int num, int pos, int val, int bits)
{
	val = ((val >>  ((pos - bits))) & ((1 << bits) -1));
	num = (num & ((~0) << bits));
	return num | val;
}

int main(int argc, int *argv[])
{
	int num , pos, val, bits;
	printf("Enter number :- ");
	scanf("%d", &num);
	printf("Enter position :- ");
	scanf("%d", &pos);
	printf("Enter no of bits :- ");
	scanf("%d", &bits);
	printf("Enter the value from which :- ");
	scanf("%d", &val);
	print_bits(num);
	print_bits(val);
	int ret = set_nth_bit(num, pos, val, bits);
	printf("New number = %d\n", ret);
	print_bits(ret);


}
