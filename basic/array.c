#include <stdio.h>

void foo(int **a, int m, int n) {
  int i = 1;
  int j = 1;
  printf("a[%d][%d]=%d\n", i, j, a[i][j]);
}

int main() {
  int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
  int *p[3];

  p[0] = a[0];
  p[1] = a[1];
  p[2] = a[2];
  foo(p, 2, 3);
}
