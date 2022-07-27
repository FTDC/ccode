//
// Created by Administrator on 2022/7/27.
//


#include <stdio.h>

// 先找到最小的时候买， 最大的时候卖出
int maxProfit(int *prices, int pricesSize) {
    int max = 0;
    for (int i = 0; i < pricesSize; ++i) {

    }

}

int main() {
    int price[] = {7, 1, 5, 3, 6, 4};
    int res = maxProfit(price, sizeof(price) / sizeof(int));

    printf("res: %d \n", res);
    return 0;
}