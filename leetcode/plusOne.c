#include <stdio.h>
#include <stdlib.h>

// int *plusOne2(int *digits, int digitsSize, int *returnSize) {

//   int *res = (int *)malloc(sizeof(int) * (digitsSize + 1));
//   int update = 1;

//   for (int i = digitsSize - 1; i >= 0; i--) {
//     // 如果位数 9 ， 上一位也 + 1
//     if ((digits[i]) == 9) {
//       res[i] = 0;
//       update = 1;
//     } else {
//       res[i] += 1;
//       update = 0;
//     }
//   }
//   returnSize = res;
//   return returnSize;
// }

int *plusOne(int *digits, int digitsSize, int *returnSize) {
  int i = 0;
  int update = 1;
  int *temp = (int *)malloc(sizeof(int) * digitsSize);
  int *tempbak = NULL;
  *returnSize = digitsSize;

  //判断是否需要进位
  for (i = digitsSize - 1; i >= 0; i--) {
    if ((digits[i] + update) == 10) {
      temp[i] = 0;
      update = 1;
    } else {

      temp[i] = digits[i] + update;
      update = 0;
    }
  }

  //如果位数超过当前数组的最大值
  if (update) {
    *returnSize = digitsSize + 1;
    tempbak = (int *)malloc((sizeof(int)) * (digitsSize + 1));
    tempbak[0] = 1;
    for (i = 0; i < digitsSize; i++) {
      tempbak[i + 1] = temp[i];
    }
    free(temp);
    return tempbak;
  }
  *returnSize = digitsSize;
  return temp;
}

int main(int argc, char const *argv[]) {
  int digits[] = {1, 2, 3};
  int* returnSize, res;
  res = plusOne(digits, sizeof(digits) / sizeof(int), returnSize);

  //   for (int i = 0; i < 5; i++) {
  printf("%d \n", res);
  //   }
  return 0;
}