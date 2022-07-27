#include <stdio.h>

int getMinimumTime(int *time, int timeSize, int **fruits, int fruitsSize,
                   int *fruitsColSize, int limit) {
    return 5;
}

int main() {
    int time[] = {2, 3, 2}, fruits[3][2] = {{0, 2},
                                            {1, 4},
                                            {2, 1}}, limit = 3;

    int min = getMinimumTime(time, 3, fruits, sizeof(fruits) / sizeof(fruits[0]),
                             sizeof(fruits[0]) / sizeof(int), limit);

    printf("最小值为：%d \n", min);
    return 0;
}