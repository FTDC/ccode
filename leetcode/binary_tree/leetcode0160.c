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
 *  判断内容是否设置过
 * @param headA
 * @param headB
 * @returnß
 */
struct ListNode *getIntersectionNode(struct ListNode *headA, struct ListNode *headB) {

    // 如果链表A和链表B
    while (headA && headB) {
        printf("str:: %d \n", headA->val);
        headA = headA->next;

        printf("str:: %d \n", headB->val);
        headB = headB->next;

        if(headA== headB){
            return true;
        }
    }

    return  NULL;

//    while (headB){
//        printf("str:: %d \n", headB->val);
//        headB = headB->next;
//    }
}