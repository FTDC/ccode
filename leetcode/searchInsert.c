#include <stdio.h>

int searchInsert(int *nums, int numsSize, int target) {
    int index = 0;
    for (int i = 0; i < numsSize;) {
        int a = i;

        // printf("i:%d, item:%d \n", target, nums[i]);
        if (nums[i] == target) {
            //   printf("i:%d, item:%d \n", i, nums[i]);
            return i;
        } else if (nums[i] > target) {
            printf("item:%d \n", nums[i]);
            return a;
        } else if (nums[i] < target && i == (numsSize - 1)) {
            return numsSize;
        }
        i += 1;
    }

    return index;
}

/**
 * @brief  二分查找法
 *
 * @param nums
 * @param numsSize
 * @param target
 * @return int
 */
int searchInsert2(int *nums, int numsSize, int target) {
    int left = 0, right = numsSize - 1, ans = numsSize;

    while (left <= right) {
        // 向左移等于除以2 , 同理向右移乘以2
        int mid = ((right - left) >> 1) + left;
        printf("left:%d, right:%d, param:%d, mid:%d \n", left, right,
               16 >> 2, mid);

        if (target <= nums[mid]) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}

int main() {

    int arr[] = {1, 3, 5, 6}, target = 2;
    int res = searchInsert2(arr, sizeof(arr) / sizeof(int), target);
    printf("res：%d \n", res);
    return 0;
}