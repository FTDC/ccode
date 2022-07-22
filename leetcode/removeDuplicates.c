#include <stdio.h>

int removeDuplicates(int *nums, int numsSize) {
  int c = numsSize;

  for (int i = 0; i < numsSize; i++) {
    int start = i;
    // 如果当前元素和下一个相等
    if (nums[i] == nums[i + 1]) {
      while (start < numsSize - 1) {
        nums[start] = nums[start + 1];
        printf("%d \n", start);
        start += 1;
      }
      c--;
    }
  }

  return c;
}

int main() {
  int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

  int len = sizeof(nums) / sizeof(int);
  int res = removeDuplicates(nums, len);

  for (int i = 0; i < len; i++) {
    printf("%d \n", nums[i]);
  }

  printf("res:%d \n", res);
  return 0;
}