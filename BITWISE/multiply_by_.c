#include "header.h"

int multiply_by(int num)
{
	return  num << "Shifting value";
	//for 2 , << 1
	//for 4 , << 2
	//for 8 , << 3
	//for 16 , << 4
	//and so on
}

int main(int argc, int *argv[])
{
	int num , pos;
	printf("Enter number :- ");
	scanf("%d", &num);

	int ret = multiply_by(num);
	printf("new number =  %d\n", ret);

	return 0;
}
