#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    int a = 0;
    int b = ~a;
    printf("b = %d \n", b);


    // exten
    extern g_num;
    printf("%d", g_num);
    return 0;
}
