#include "header.h"

int main()
{
	int num;
	printf("Enter the number :- ");
	scanf("%d", &num);

	if((num & (num - 1)))
		printf("%d Not a power of 2\n", num);
	else
		printf("%d is a power of 2\n", num);

}
