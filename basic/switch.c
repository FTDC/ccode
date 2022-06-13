
#include <stdio.h>

int main(int argc, char const *argv[])
{

    for (int i = 0; i < 100; i++)
    {
        if (i % 2 == 1)
        {
            printf("num: %d\n", i);
        }

        switch (i % 3)
        {
        case 1:
            printf("switch num: %d\n", i);
            break;
            default:
            printf("switch nomal num: %d\n", i);
            break;

        }
    }
    return 0;
}
