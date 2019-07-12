#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct 
{
    double a;
    unsigned long long int* b;
}float_tun;

float_tun float_un;


int main() 
{
    float_un.a  = 12.912768;
    float_un.b = &float_un.a;
    
    printf("%llx\n", *(float_un.b));

    return 0;
}
