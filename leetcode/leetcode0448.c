//
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//

#include <stdio.h>
#include <malloc.h>


int *findDisappearedNumbers(int *nums, int numsSize, int *returnSize) {
    int *res = malloc(numsSize * sizeof(int));

    int tmp = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] != i) {
            tmp = nums[i];
            nums[i] = nums[nums[i]];
            nums[nums[i]] = tmp;
        }
        printf("%d \n", nums[i]);
    }

    *returnSize = 0;

    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] == 0) {
            res[*returnSize++] = i;
        }
    }
    return res;
}

int main(int argc, char const *argv[]) {
    int nums[] = {4, 3, 2, 7, 8, 2, 3, 1};
    int *returnSize;
    int *res = findDisappearedNumbers(nums, sizeof(nums) / sizeof(int), returnSize);

    for (int i = 0; i < *returnSize; i++) {
        printf("item:%d \n", res[i]);
    }
    return 0;
}