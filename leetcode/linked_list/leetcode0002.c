/**
 * @file
 * @brief 给你一个二叉树的根节点 root ， 检查它是否轴对称。
 * @version 0.1
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdbool.h>
#include <stdio.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node;


struct ListNode *addTwoNumbers(struct ListNode *l1, struct ListNode *l2) {

    while (l1 || l2) {

        printf("int::%d , l2:%d\n", l1->val, l2->val);
        l1->val = l1->val + l2->val;
        l1 = l1->next;
        l2 = l2->next;
    }

    return l1;

}

int main(int argc, char const *argv[]) {

    // 先声明一个二叉树
    Node listNode1;
    Node listNode2;
    Node listNode3;
    Node listNode4;
    Node listNode5;
    Node listNode6;

    listNode1.val = 2;
    listNode1.next = &listNode2;

    listNode2.val = 4;
    listNode2.next = &listNode5;

    listNode3.val = 3;
    listNode3.next = NULL;

    listNode4.val = 5;
    listNode4.next = &listNode5;

    listNode5.val = 6;
    listNode5.next = &listNode6;

    listNode6.val = 7;
    listNode6.next = NULL;

    struct ListNode *res = addTwoNumbers(&listNode1, &listNode4);

    while (res) {
        res = res->next;
        printf("%d \n", res->val);
    }


    return 0;
}

