/**
 * @file
 * @version 0.1
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node;


/**
 *  翻转链表
 * @param head
 * @return
 */
struct ListNode *reverseList(struct ListNode *head) {

    // 记住上一个节点的信息
    struct ListNode *curNode = head, *preNode = NULL;

    while (curNode) {
        // 下一個节点
        struct ListNode *nextNode = curNode->next;
        // 当前节点的内容等于上一个节点地址
        curNode->next = preNode;
        // 把当前节点赋值给上一个节点
        preNode = curNode;
        // 当前节点等于下一个节点
        curNode = nextNode;
    }

    return preNode;
}


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
    listNode2.next = &listNode3;

    listNode3.val = 3;
    listNode3.next = &listNode4;

    listNode4.val = 4;
    listNode4.next = &listNode5;

    listNode5.val = 5;
    listNode5.next = NULL;

    struct ListNode *res = reverseList(&listNode1);

    printf("%d \n", res->val);

    return 0;
}


