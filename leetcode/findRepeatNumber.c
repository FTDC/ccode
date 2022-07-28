#include <stdio.h>

int findRepeatNumber(int *nums, int numsSize) {
    printf("总共多少个：%d \n", numsSize);

    int len = 0;

    // 声明一个同样长度的数组
    // int arr[numsSize] = {0};
    while (len < numsSize) {


        if (nums[len] == len) {
            ++len;
            continue;
        }

        // printf("nums:%d \n", nums[len]);

        if (nums[len] == nums[nums[len]]) {
            return nums[len];
        } else {
            int temp = nums[len];
            nums[len] = nums[temp];
            nums[temp] = temp;
        }


        // arr[]
    }

    return -1;
}

int main(int argc, char const *argv[]) {
    int arr[] = {12, 3, 1, 0, 2, 5, 3};

    int c = findRepeatNumber(arr, sizeof(arr) / sizeof(int));

    printf("res:%d", c);
    return 0;
}
