#include <stdio.h>
#include <string.h>

int lengthOfLastWord(char *s) {
  int len = 0, l = strlen(s);
  const char limmiter[] = "-";

  int g = 0;

  for (int i = l - 1; i >= 0; i--) {

    l--;
    // printf("%c \n", s[i]);
    if ((s[i]) == ' ' && g > 0) {
      return g;

      // printf("%s \n", l);
      printf("gg=%d \n", l);
    } else if (s[i] != ' ') {
      g++;
    }
  }

  // 判断最后一个单词
  // const char limmiter[2] = "-";
  // char *res = strtok(s, limmiter);

  // /* 继续获取其他的子字符串 */
  // while (res != NULL) {
  //   printf("item:%s\n", res);
  //   res = strtok(NULL, s);
  // }

  return g;
}

int main(int argc, char const *argv[]) {
  char str[] = "hello world";

  int res = lengthOfLastWord(str);

  printf("%d \n", res);
  return 0;
}