#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef union {
    unsigned char data_uc;
    unsigned short data_us;
    unsigned int data_ui;
    unsigned long long data_ull;
}Data_tun;
Data_tun Data_un; 

char st[9] = {0};

void pad_zeros(char *value, unsigned char zeros)
{
    memset(st, 0, sizeof(st));
    char zero[2] = "0";
    for (int i = 0; i < zeros; i++)
    {
        strcat(st, zero);
    }
    sprintf(st,"%s%s",st, value);
}

void padd_num(void *param, char i)
{
    unsigned char Datalength;
    char str[19] = {0};

    if (i == 1) {
        Data_un.data_uc = *(unsigned char *)(param);
        sprintf(str,"%x", Data_un.data_uc);
        Datalength = strlen(str);
        pad_zeros(&str, ((i * 2) - Datalength));
        printf("%x , %s\n", Data_un.data_uc, st);
    }
    else if (i == 2) {
        Data_un.data_us = *(unsigned short *)(param);
        sprintf(str,"%x", Data_un.data_us);
        Datalength = strlen(str);
        pad_zeros(&str, ((i * 2) - Datalength));
        printf("%x , %s\n", Data_un.data_us, st);
    }
    else if (i == 4) {
        Data_un.data_ui = *(unsigned int *)(param);
        sprintf(str,"%x", Data_un.data_ui);
        Datalength = strlen(str);
        pad_zeros(&str, ((i * 2) - Datalength));
        printf("%x , %s\n", Data_un.data_ui, st);
    }
    else if (i == 8) {
        Data_un.data_ull = *(unsigned long long *)(param);
        sprintf(str,"%llx", Data_un.data_ull);
        Datalength = strlen(str);
        pad_zeros(&str, ((i * 2) - Datalength));
        printf("%llx , %s\n", Data_un.data_ull, st);
    }
    return;    
}

int main() {
    {
        unsigned char num = 0;
        padd_num(&num, sizeof(num));
    }
    {
        unsigned short num = 0;
        padd_num(&num, sizeof(num));
    }
    {
        unsigned int num = 0;
        padd_num(&num, sizeof(num));
    }
    {
        unsigned long long num = 0;
        padd_num(&num, sizeof(num));
    }
    return 0;
}