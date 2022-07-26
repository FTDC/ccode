#include <stdio.h>

int removeDuplicates(int *nums, int numsSize) {

  if (numsSize == 0) {
    return 0;
  }
  int fast = 1, slow = 1;
  while (fast < numsSize) {
    if (nums[fast] != nums[fast - 1]) {
      nums[slow] = nums[fast];
      ++slow;
    }
    ++fast;
  }
  return slow;
}

int main() {
  int nums[] = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};
  //   int nums[] = {1, 2};

  int len = sizeof(nums) / sizeof(int);
  int res = removeDuplicates(nums, len);

  printf("%s \n", "结果内容");
  for (int i = 0; i < len; i++) {
    printf("%d \n", nums[i]);
  }

  printf("res:%d \n", res);
  return 0;
}