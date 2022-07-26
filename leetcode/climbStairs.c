#include <stdio.h>

/**
 * @brief 假设你正在爬楼梯。需要 n 阶你才能到达楼顶。每次你可以爬 1 或 2
 * 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 */

 // 1 1 2 3 5 

int climbStairs(int n) {
  int p = 0, q = 0, r = 1;
  for (int i = 1; i <= n; ++i) {
    p = q;
    q = r;
    r = p + q;
  }
  return r;
}

int main(int argc, char const *argv[]) {
  int n = 10;
  int res = climbStairs(n);
  printf("%d \n", res);
  return 0;
}