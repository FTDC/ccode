#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a = 160;
    int b = 25;
    int r = 1;

    while (a % b)
    {
        r = a % b;
        a = b;
        b = r;
    }

    printf("最大公约数为 %d", r);
    return 0;
}


// r  10     5   0   
// a 160    25   10  
// b  25    10   5   