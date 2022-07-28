//
// Created by Administrator on 2022/7/27.
//



#include <stdio.h>
#include <math.h>
#include <limits.h>

//#define   FMAX(x, y) (x>y)?x:y

// 先找到最小的时候买，找到最小值下标后找最大的时候卖出  -- 错误想法
// 找出相差值最大的两个数字
int maxProfit1(int *prices, int pricesSize) {
    int max = 0;
    int res = 0;

    for (int i = 0; i < pricesSize; ++i) {
        for (int j = i; j < pricesSize; ++j) {
//            printf("j:%d, i:%d, fmax:%d \n", j, i, max);
            max = prices[j] - prices[i];
            res = fmax(res, max);
        }
    }
    if (res > 0) {
        return res;
    }
    return 0;
}


/**
 *  假设第一次就是最低价格买入 ， 每次计算获取最小值
 * @param prices
 * @param pricesSize
 * @return
 */
int maxProfit(int *prices, int pricesSize) {
    int minPrice = INT_MAX;
    int res = 0;

    for (int i = 0; i < pricesSize; ++i) {
        if (prices[i] < minPrice) {
            minPrice = prices[i];
        } else if (prices[i] - minPrice > res) {
            res = prices[i] - minPrice;
        }
//            printf("j:%d, i:%d, fmax:%d \n", j, i, max);
//            max = prices[j] - prices[i];
//            res = fmax(res, max);
    }
    return res;
}


int main() {
    int price[] = {7, 1, 5, 3, 6, 4};
    int res = maxProfit(price, sizeof(price) / sizeof(int));

    printf("res: %d \n", res);
    return 0;
}