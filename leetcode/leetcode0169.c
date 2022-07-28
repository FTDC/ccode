//
// Created by Administrator on 2022/7/27.
//



#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>


int *compareFunc(const int *a, const int *b) {
    return *((int *) a) - *((int *) b);
}

/**
 *  先排序， 然后取一半以上的值
 * @param nums
 * @param numsSize
 * @return
 */
int majorityElement(int *nums, int numsSize) {
    qsort(nums, numsSize, sizeof(int), compareFunc);
    for (int i = 0; i < numsSize; ++i) {
        printf("int:: %d \n", nums[i]);
    }
    return nums[numsSize / 2];
}

/**
 *  抵消
 * @param nums
 * @param numsSize
 * @return
 */
int majorityElement2(int *nums, int numsSize) {
    int count = 1, majority = nums[0];
//    qsort(nums, numsSize, sizeof(int), compareFunc);
    for (int i = 1; i < numsSize; ++i) {
        if (nums[i] == majority) {
            count++;
        } else {
            count--;
            if (count == 0) {
                majority = nums[i];
            }
        }


//        printf("int:: %d \n", nums[i]);
    }
    return majority;
}


int main() {
//    int price[] = {2, 2, 1, 1, 1, 2, 2};
    int price[] = {3,2,3};
//    int price[] = {3, 3, 4};
    int res = majorityElement2(price, sizeof(price) / sizeof(int));

    printf("res: %d \n", res);
    return 0;
}