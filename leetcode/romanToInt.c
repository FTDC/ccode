#include <stdio.h>
#include <string.h>

/**
 * @brief 根据字符获取对应的罗马数字
 *
 * @param k
 * @return int
 */
int getCharValue(char k) {
  int value = 0;
  switch (k) {
  case 'I':
    value = 1;
    break;
  case 'V':
    value = 5;
    break;
  case 'X':
    value = 10;
    break;
  case 'L':
    value = 50;
    break;
  case 'C':
    value = 100;
    break;
  case 'D':
    value = 500;
    break;
  case 'M':
    value = 1000;
    break;
  }

  return value;
}

int romanToInt(char *s) {
  int sum = 0;
  // 判断字符串长度
  int len = strlen(s);

  printf("字符串长度：%d \n", len);

  for (int i = 0; i < len; i++) {
    char key = s[i];

    int temp = getCharValue(key);
    printf("字符：%c，值：%d \n", key, temp);

    // 因为罗马数字， 大的在左边 ， 如果判断上一个字符比当前小则需要减去
    if ((i < len - 1) && temp < getCharValue(s[i + 1])) {
      sum -= temp;
    } else {
      sum += temp;
    }
  }

  return sum;
}

int romanToInt2(char *s) {
  int symbolValues[26];
  symbolValues['I' - 'A'] = 1;
  symbolValues['V' - 'A'] = 5;
  symbolValues['X' - 'A'] = 10;
  symbolValues['L' - 'A'] = 50;
  symbolValues['C' - 'A'] = 100;
  symbolValues['D' - 'A'] = 500;
  symbolValues['M' - 'A'] = 1000;
  int ans = 0;
  int n = strlen(s);
  for (int i = 0; i < n; ++i) {
    int value = symbolValues[s[i] - 'A'];
    if (i < n - 1 && value < symbolValues[s[i + 1] - 'A']) {
      ans -= value;
    } else {
      ans += value;
    }
  }
  return ans;
}

int main() {
  char str[] = "IIV";
  // int res = romanToInt(str);
  int res = romanToInt2(str);
  printf("计算结果：%d", res);
  return 0;
}
