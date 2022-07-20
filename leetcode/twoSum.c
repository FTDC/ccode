//
// Created by Administrator on 2022/7/7.
//

#include <stdio.h>
#include <string.h>
#include <malloc.h>

int *twoSum(int *nums, int numsSize, int target, int *returnSize) {
    int start = 0, cur = 1;
//    returnSize = {0, 1};
    int *res = malloc(sizeof(int) * 2);
    while (start < numsSize - 1) {
        if (nums[start] + nums[cur] == target) {
            *returnSize = 2;
            res[0] = start;
            res[1] = cur;
            return res;

        } else {
            cur++;
        }
        if (cur < numsSize - 1) {
            start++;
            cur = start + 1;
        }

    }
    *returnSize = 0;
    return res;
}


int main() {

    int nums[4] = {2, 7, 11, 15};
    int target = 26;

    int size[] = {};
    int *res;

    *res = twoSum(nums, 4, target, size);

    printf("one: %d, two:%d", res[0], res[1]);

    return 0;
}