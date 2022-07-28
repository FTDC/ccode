#include <math.h>
#include <stdio.h>

int maxSubArray(int *nums, int numsSize) {

    int sum = nums[0], pre = 0;
    for (int i = 1; i < numsSize; i++) {

        if (nums[i] + nums[i - 1] > nums[i]) {
            nums[i] += nums[i - 1];
        }
        if (nums[i] > sum) {
            sum = nums[i];
        }

        // pre += nums[i];
        // if (pre > sum) {
        //   //   printf("%d ,i:%d, item:%d\n", sum, i, nums[j]);
        //   sum = pre;
        // }

        // printf("sum:%d \n", sum);
    }

    return sum;
}

int maxSubArray2(int *nums, int numsSize) {
    int pre = 0, maxAns = nums[0];
    for (int i = 0; i < numsSize; i++) {
        pre = fmax(pre + nums[i], nums[i]);
        maxAns = fmax(maxAns, pre);
    }
    return maxAns;
}

int main() {
    int nums[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    //   int nums[] = {-2, -1};
    int res = maxSubArray(nums, sizeof(nums) / sizeof(int));

    printf("res:%d \n", res);
}