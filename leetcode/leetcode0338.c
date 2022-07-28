//
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//

#include <stdio.h>
#include <malloc.h>


int countOneBits(int n) {
    int c = 0;
    while (n > 0) {
        n = n & (n - 1);
        c++;
    }
    return c;
}

/**
 *  解决思路是每次跟相邻的数字取---- Brian Kernighan 算法
 * @param n
 * @param returnSize
 * @return
 */
int *countBits(int n, int *returnSize) {
    int *new = malloc(sizeof(int) * (n + 1));
    returnSize = n + 1;
    int c = 0;
    for (int i = 0; i <= n; ++i) {
        c = countOneBits(i);
        printf("%d \n", c);
        new[i] = c;
    }

    return new;
}

/**
 *方法二：动态规划——最高有效位
 * @param n
 * @param returnSize
 * @return
 */
int *countBits2(int n, int *returnSize) {
    int *bits = malloc(sizeof(int) * (n + 1));
    *returnSize = n + 1;
    bits[0] = 0;
    int highBit = 0;
    for (int i = 1; i <= n; i++) {
        if ((i & (i - 1)) == 0) {
            highBit = i;
        }
        bits[i] = bits[i - highBit] + 1;
    }
    return bits;
}


/**
 * 方法三：动态规划——最低有效位
 * @param n
 * @param returnSize
 * @return
 */
int *countBits3(int n, int *returnSize) {
    int *bits = malloc(sizeof(int) * (n + 1));
    *returnSize = n + 1;
    bits[0] = 0;
    for (int i = 1; i <= n; i++) {
        bits[i] = bits[i >> 1] + (i & 1);
    }
    return bits;
}


/**
 * 方法四：动态规划——最低设置位
 *
 * @param n
 * @param returnSize
 * @return
 */
int *countBits4(int n, int *returnSize) {
    int *bits = malloc(sizeof(int) * (n + 1));
    *returnSize = n + 1;
    bits[0] = 0;
    for (int i = 1; i <= n; i++) {
        bits[i] = bits[i & (i - 1)] + 1;
    }
    return bits;
}


int main(int argc, char const *argv[]) {
    int nums = 5;
    int *returnSize;
    int *res = countBits2(nums, returnSize);
    for (int i = 0; i < *returnSize; i++) {
        printf("item:%d \n", res[i]);
    }
    return 0;
}