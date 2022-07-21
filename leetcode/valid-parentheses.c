#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char pairs(char a) {
  if (a == '}')
    return '{';
  if (a == ']')
    return '[';
  if (a == ')')
    return '(';
  return 0;
}

bool isValid(char *s) {
  int slen = strlen(s);
  if (slen % 2 != 0) {
    return false;
  }

  // if (s[0] != pairs(slen - 1)) {
  //   return false;
  // }

  // int loop = floor(slen / 2);
  int top = 0;
  // 栈结构, 先进后出 ， 匹配最近的一个对称的符号
  char stk[slen];

  for (int i = 0; i < slen; i++) {
    char ch = pairs(s[i]);
    if (ch) {
      if (top == 0 || stk[top - 1] != ch) {
        return false;
      }
      top--;
    } else {
      stk[top++] = s[i];
    }
  }

  return top == 0;
}

int main() {

  char str[] = "(([]){})";
  bool res = isValid(str);

  printf("%d \n", res);

  return 0;
}