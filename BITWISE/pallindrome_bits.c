#include "header.h"

int pallindrome_bits(int num)
{
	int j = 0;
	for (int k = 31; k >= 0;k--)
	{
		if (num & (1 << k))
		{
			for (int i = k; i >= k/2; i--, j++)
			{
				if (!( (num & (1 << i)) && (num & (1 << j)) || ( !(num & (1 << i)) && !(num & (1 << j))) ))
					return 0;
			}
			return 1;
		}
	}
}

int main(int argc, int * argv[])
{
	int num;
	printf("Enter the number :- ");
	scanf("%d", &num);

	int ret = pallindrome_bits(num);
	print_bits(num);
	if (ret)
		printf("bits are pallindrome\n");
	else
		printf("bits are not pallindrome\n");
	
	return 0;
}
