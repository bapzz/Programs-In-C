/*
 * =====================================================================================
 *
 *       Filename:  odd_even.c
 *
 *    Description:  
 *
 *        Created:  Sunday 01 October 2017 05:18:40  IST
 *         Author:  Biswajeet Sahoo <biswajeet21sahoo@gmail.com>
 *
 * =====================================================================================
 */
 
#include "header.h"

int main()
{
	int num, count = 0;;
	printf("Enter NUmber :- ");
	scanf("%d", &num);
#if 0
	for (int i = 31; i >= 0; i--)
	{
		if ((num & (1 << i)) && ((num & 1)==0))
			count++;
	}
	if(count)
		printf("EVEN\n");
	else
		printf("ODD\n");
#endif
#if 1
	if(num & 1)
		printf("ODD NUmber\n");
	else
		printf("EVEN Nmber\n");
#endif
}


