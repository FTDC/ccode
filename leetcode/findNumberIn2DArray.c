#include <stdio.h>
//添加头文件 
#include <stdbool.h>

bool findNumberIn2DArray(int **matrix, int matrixSize)
{
    printf("matrix:%d \n", **matrix);

    if (matrix > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int main(int argc, char const *argv[])
{

    int matrix[5][5] = {1, 4, 7, 11, 15, 2, 5, 8, 12, 19, 3, 6, 9, 16, 22, 10, 13, 14, 17, 24, 18, 21, 23, 26, 30};

    // int **p = matrix;

    findNumberIn2DArray(matrix, 5);

    /* code */
    return 0;
}
