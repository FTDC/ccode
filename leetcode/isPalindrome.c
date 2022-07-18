#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// _Bool isPalindrome(int x) {

//   // 判断参数必须大于9， 否则没有比较的内容
//   if (x < 10) {
//     return false;
//   }
//   // 先转换数字转成字符串

//   return true;
// }

int main()
{

  //   _Bool res = isPalindrome(121);

  int num = 121;

  int len = sizeof(num) / sizeof(int);

  char a[100];

  //这里后面有讲哈。把整数x，转化为字符串存入a中
  sprintf(a, "%d", x);

  printf("%d \n", len);

  //  printf("%s \n", num);

  // printf(" %d \n", res);
  return 0;
}