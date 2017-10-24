#include "header.h"

int get_n_bits_pos(int num, int pos, int bits)
{
	return ((num >> (pos - bits)) & ((1 << bits) -1 ));
}

int main(int argc, int *argv[])
{
	int num , pos,bits;
	printf("Enter number :- ");
	scanf("%d", &num);
	printf("Enter position :- ");
	scanf("%d", &pos);
	printf("Enter no of bits :- ");
	scanf("%d", &bits);
	
	print_bits(num);
	int ret = get_n_bits_pos(num, pos, bits);
	printf("New number = %d\n", ret);
	print_bits(ret);


}
