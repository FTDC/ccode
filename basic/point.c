#include <stdio.h>

int main(int argc, char const *argv[])
{
    /* code */
    char name = 'c';

    char *p = &name;

    *p = 'd';

    printf("char: %c", name);
    return 0;
}
