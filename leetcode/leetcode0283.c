//
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//

#include <stdio.h>


void moveZeroes(int *nums, int numsSize) {
    int c = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != 0) {
            nums[c++] = nums[i];
        }
    }
    for (int i = c; i < numsSize; ++i) {
        nums[i] = 0;
    }
}


int main(int argc, char const *argv[]) {

    int nums[] = {0, 1, 0, 3, 12};
    moveZeroes(nums, 5);
    for (int i = 0; i < 5; i++) {
        printf("%d \n", nums[i]);
    }
    return 0;
}