#include <stdio.h>
#include "../include/static_lib.h"

int main(void)
{
    int a = 0;
    int b = 0;
    int i = 0;
    for(i = 0;i<1000;i++)
    {
        a++;
        b++;
        printf("a+b=%d\n",add(a,b));
        sleep(1);
    } 
    return 0;
}
