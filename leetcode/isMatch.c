#include <stdio.h>
#include <string.h>

int isMatch(char *s, char *p) {
  // 判断是否存在, 特殊符号（。, *）
  int slen = strlen(s);
  int plen = strlen(p);
  int a = 0;
  //   printf("元字符：%d \n", slen);
  //   if (strcmp(p, '*')) {
  //     return 1;
  //   }

  // 判断内容里面存在特殊字符
  if (p == ".*" || p == "." || p == "*") {
    a = 1;
  }

  // 逐个对比   aname  a.n
  for (int j = 0; j < plen; j++) {

    for (int i = 0; i < slen; i++) {
      //   printf("%c\n", p[j]);
      if (strcmp(&p[j], &s[i]) || (p[i] == "*") || (p[i] == ".")) {
        a = 1;
        continue;
      } else {
        a = 0;
      }
    }
  }

  return a;
}

int main(int argc, char const *argv[]) {
  char s[] = "aeeea", p[] = "a.c";

  printf("%s \n", s);
  int res = isMatch(s, p);
  printf("result: %d", res);
  return 0;
}
