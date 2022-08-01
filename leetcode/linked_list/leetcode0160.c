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


struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB);

int main(int argc, char const *argv[]) {

    // 先声明一个二叉树
    Node listNode1;
    Node listNode2;
    Node listNode3;
    Node listNode4;
    Node listNode5;

    listNode1.val = 1;
    listNode1.next = &listNode2;

    listNode2.val = 2;
    listNode2.next = &listNode5;

    listNode3.val = 3;
    listNode3.next = &listNode4;

    listNode4.val = 4;
    listNode4.next = &listNode5;

    listNode5.val = 5;
    listNode5.next = NULL;

    struct ListNode *res = getIntersectionNode(&listNode1, &listNode3);

    printf("%d \n", res->val);

    return 0;
}


/**
 *  用双指针pA 、pB循环俩个链表，链表A循环结束就循环链表B，链表A循环结束就循环链表B，当pA == pB时就是交点，因为两个指针移动的步数一样
 *
 * @param headA
 * @param headB
 * @returnß
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {

    // 任何一个为空则没有交集
    if (headA == NULL || headB == NULL) {
        return NULL;
    }

    // 变量声明是为了存储各自原生表头
    struct ListNode *pA = headA, *pB = headB;

    // 如果链表A和链表B 不相等， 声明两个循环完成肯定有结束的时候
    while (pA != pB) {
        // 循环一遍如果为NUll ，这只为headB的链表头
        pA = (pA ? pA->next : headB);
        pB = (pB ? pB->next : headA);
    }

    return pA;
}