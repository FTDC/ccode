#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int strStr2(char *haystack, char *needle) {
  int n = strlen(haystack), m = strlen(needle);
  for (int i = 0; i + m <= n; i++) {
    bool flag = true;
    for (int j = 0; j < m; j++) {
      if (haystack[i + j] != needle[j]) {
        flag = false;
        break;
      }
    }
    if (flag) {
      return i;
    }
  }
  return -1;
}

int strStr(char *haystack, char *needle) {
  int index = 0;
  //   // 对比字符
  //   if (needle == NULL) {
  //     return index;
  //   }

  //   // 找不到默认为-1
  //   index = -1;

  int srclen = strlen(haystack), destlen = strlen(needle);

  for (int i = 0; i + destlen <= srclen; i++) {
    // printf("%c , %c\n", *(haystack + i), *needle);

    int flag = true;
    //   printf("%d \n", i);
    for (int j = 0; j < destlen; j++) {
      printf("%d, %c , %c\n", j, *(haystack + i + j), *(needle + j));
      if ((haystack[i + j]) != (needle[j])) {
        flag = false;
        break;
      }
    }

    if (flag == true) {
      return  i;
    //   break;
    }
  }

  return index;
}

int main() {
  //   char haystack[] = "a", needle[] = "a";
  char haystack[] = "aaa", needle[] = "a";
  //   char haystack[] = "aaaaa", needle[] = "bba";

  int res = strStr(haystack, needle);
  printf("%d \n", res);

  return 0;
}