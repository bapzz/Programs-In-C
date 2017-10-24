#include "header.h"

int clear_bit(int num, int pos)
{
	return num & ~(1 << pos - 1);
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);
	printf("Enter position :- ");
	scanf("%d", &pos);

	int ret = clear_bit(num, pos);
	printf("New number = %d\n", ret);


}
