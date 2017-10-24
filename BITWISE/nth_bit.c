#include "header.h"
#define SET 1
#define NOT_SET 0
int nth_bit(int num, int pos)
{
	if(num & (1 << pos - 1))
		return SET;
	else
		return NOT_SET;
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);
	printf("Enter position :- ");
	scanf("%d", &pos);

	int ret = nth_bit(num, pos);
	if (ret)
		printf("SET\n");
	else
		printf("not SET\n");


}
