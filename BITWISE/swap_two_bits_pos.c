#include "header.h"

int swap_pos(int num, int pos1, int pos2)
{
	if ((num & (1 << (pos1 - 1))) && (num & (1 << (pos2 - 1))))
	{
		printf("No Need to swap, both positions are equal\n");
		return num;
	}
	if (!(num & (1 << (pos1 - 1))) && !(num & (1 << (pos2 - 1))))
	{
		printf("No Need to swap, both positions are equal\n");
		return num;
	}

	num = num ^ (1 << (pos1 - 1));
	num = num ^ (1 << (pos2 - 1));

	return num;
}
int main(int argc, int * argv[])
{
	int num, pos1, pos2;
	printf("Enter the number :- ");
	scanf("%d", &num);
	printf("Enter the position 1 :- ");
	scanf("%d", &pos1);
	printf("Enter the position 2 :- ");
	scanf("%d", &pos2);

	int ret = swap_pos(num, pos1, pos2);
	
	printf("New number = %d\n", ret);
	return 0;
}
