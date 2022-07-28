//
// Created by eric on 2022/7/28.
//

#include <stdio.h>

int singleNumber(int *nums, int numsSize) {
    for (int i = 1; i < numsSize; ++i) {
        // 数字 异或计算原来的数就会抵消
        nums[0] ^= nums[i];
    }
    return nums[0];
}

int main() {
    int nums[] = {2, 2, 1};
    int res = singleNumber(nums, sizeof(nums) / sizeof(int));
    printf("res:%d \n", res);
    return 0;
}
