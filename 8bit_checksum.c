#include <stdio.h>
#include <string.h>
#include <stdlib.h>

unsigned char bt_calculate_checksum(char * ptrexArray)
{
    unsigned char len = strlen(ptrexArray)/2;
    unsigned char str[3];
    unsigned char checksum = 0;
    
	printf("String = %s -- len = %d\n", ptrexArray, len);

    for (int i = 0; i < len; i++)
	{
		strncpy (str, ptrexArray, 2);
		checksum = (unsigned int)checksum + (unsigned int)strtol(str, NULL, 16);
		ptrexArray += 2;
	}
	
#if 1 //2sComplement
	//checksum = (unsigned char)(~(checksum)) + 1;
	checksum = 0x100 - checksum;
#endif
#if 0  //Modulo 256
	checksum = checksum % 256;
#endif
	printf("cksm = %x\n", checksum);
    return checksum;
}


int main() {
	char exArray[] = "4D434750055D0C22000400000000000701500255AA2F16";
    unsigned char checksum = 0;
    
    checksum = bt_calculate_checksum(exArray);
	
	sprintf (exArray,"%s%x",exArray,checksum);

	printf("checksum = %x\n%s\n", checksum, exArray);
	
	return 0;
}
