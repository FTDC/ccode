#include <string.h>
#include <stdio.h>


union cc
{
    char c;
    int a;
    /* data */
};


int main(int argc, char const *argv[])
{
    union cc ucc;
    ucc.a = 0x11223344;

    printf("%d", ucc.c);

   
    return 0;
}
