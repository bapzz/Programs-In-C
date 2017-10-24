#include "header.h"

int toggle_without(int num)
{
	for (int i = 0; i < sizeof(int) * 8; i++)
	{
		num = num ^ (1 << i);
	}
	return num;
}

int main(int argc, int *argv[])
{
	int num;
	printf("Enter number :- ");
	scanf("%d", &num);
	print_bits(num);
	int ret = toggle_without(num);
	printf("New number = %d\n", ret);
	print_bits(ret);


}
