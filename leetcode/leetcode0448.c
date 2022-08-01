//
// 给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
//

#include <stdio.h>
#include <stdlib.h>


/**
 *  先遍历数组中的元素
 * @param nums
 * @param numsSize
 * @param returnSize
 * @return
 */

int *findDisappearedNumbers(int *nums, int numsSize, int *returnSize) {
    int *res = malloc(*returnSize * sizeof(int));

    // 原地哈希， 把1-8 当层key， 如果给这个key 增加了两次说明存在多次 ， 如果不存在则不会增加数字
    for (int i = 0; i < numsSize; ++i) {
        // 取模是让重复出现的key 加入到正确的位置
        int x = (nums[i] - 1) % numsSize;
        nums[x] += numsSize;
    }

    // 对比增加个数的元素
    for (int i = 0; i < numsSize; ++i) {
        if (nums[i] <= 8) {
            res[(*returnSize)++] = i + 1;
        }
    }

    return res;
}

int main(int argc, char const *argv[]) {
    int nums[] = {4, 3, 2, 7, 8, 2, 3, 1};
    int returnSize = 0;
    int *res = findDisappearedNumbers(nums, sizeof(nums) / sizeof(int), &returnSize);

    printf("str::%s \n", "-------------------");
    for (int i = 0; i < returnSize; i++) {
        printf("item:%d \n", res[i]);
    }
    return 0;
}