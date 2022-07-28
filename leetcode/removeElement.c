#include <stdio.h>

int removeElement(int *nums, int numsSize, int val) {

    int fast = 0, count = 0;
    while (fast < numsSize) {
        if (nums[fast] == val) {

        } else {
            nums[count++] = nums[fast];
            //   count++;
        }
        fast++;
    }
    return count;
}

int main() {
    int nums[] = {3, 2, 2, 3}, val = 3;

    int res = removeElement(nums, sizeof(nums) / sizeof(int), 3);
    for (int i = 0; i < res; i++) {
        printf("%d \n", nums[i]);
    }

    return 0;
}