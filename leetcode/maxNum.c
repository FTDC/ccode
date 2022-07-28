#include <stdio.h>
#include <string.h>

void largestNumber(int *nums, int numsSize) {
    // 先将数组的每个数组按照收个数字排序，然后转换成字符
    // for (int i = 0, i < numsSize, i++)
    // {
    //     printf("item: %d", i);
    // }

    for (int i = 0; i < numsSize; i++) {
        /* code */
        printf("item: %d", i);
    }


    // 从大往小的连接排序

    // char *res = NULL;

    // return res;
}

int main(int argc, char const *argv[]) {
    /* code */
    printf("123: d%", 123);

    int nums[2] = {10, 2};

    int numsSize = sizeof(nums) / sizeof(int);

    largestNumber(nums, numsSize);
    return 0;
}
