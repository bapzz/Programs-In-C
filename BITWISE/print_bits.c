/*
 * =====================================================================================
 *
 *       Filename:  print_bits.c
 *
 *    Description:  
 *
 *        Created:  Sunday 01 October 2017 03:49:05  IST
 *         Author:  Biswajeet Sahoo <biswajeet21sahoo@gmail.com>
 *
 * =====================================================================================
 */
int print_bits(int num)
{
	for (int i = sizeof(num)*8- 1; i >= 0; i--)
	{
		if(num &(1 << i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}


