#include "header.h"

int highest_set_bit(int num)
{
	for (int i = 31; i > 0; i--)
	{
		if (num & (1 << i))
			return i;
			//return num & (1 << i);
	}
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);

	int ret = highest_set_bit(num);
	printf("set at %dth position\n", ret);


}
