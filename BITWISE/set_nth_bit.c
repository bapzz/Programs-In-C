#include "header.h"

int set_nth_bit(int num, int pos)
{
	return (num | (1 << pos - 1));
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);
	printf("Enter position :- ");
	scanf("%d", &pos);

	int ret = set_nth_bit(num, pos);
	printf("New number = %d\n", ret);


}
