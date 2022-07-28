//
// Created by eric on 2022/7/28.
//

#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>

/**
 * 给你一个链表的头节点 head ，判断链表中是否有环。
 * @return
 */

typedef struct ListNode {
    int val;
    struct ListNode *next;
} Node;

#define MAXSIZE 769/* 选取一个质数即可 */


typedef struct Node {
    int elem;
    struct ListNode *node;  //保存地址
    struct Node *next;          //保存链表表头
} List;


typedef struct {
    List *hashHead[MAXSIZE];//定义哈希数组的大小
} MyHashSet;


bool isInHash(List *list, struct ListNode *node) {
    List *nodeIt = list;
    //通过链表下遍历
    while (nodeIt != NULL) {
        if (nodeIt->node == node) {
            return true;
        }
        nodeIt = nodeIt->next;
    }
    return false;
}

MyHashSet *myHashSetCreate() {
    int i;
    MyHashSet *newHash = (MyHashSet *) malloc(sizeof(MyHashSet));
    /* 对链表的头结点赋初值 */
    for (i = 0; i < MAXSIZE; i++) {
        newHash->hashHead[i] = NULL;
    }
    return newHash;
}

void myHashSetAdd(MyHashSet *obj, struct ListNode *node) {
    //插入在Head处
    if (isInHash(obj->hashHead[(int) node % MAXSIZE], node)) {
        //不用添加了
        return;
    }
    List *newNode = (List *) malloc(sizeof(List));
    newNode->node = node;
    newNode->next = NULL;
    if (obj->hashHead[(int) node % MAXSIZE] != NULL) {
        //当前头链表不为空，则需要将后续的链表接上
        //需要主要这里表头也代表一个数据的值
        newNode->next = obj->hashHead[(int) node % MAXSIZE];
    }
    //修改头链表
    obj->hashHead[(int) node % MAXSIZE] = newNode;

}

bool myHashSetContains(MyHashSet *obj, struct ListNode *node) {
    return isInHash(obj->hashHead[(int) node % MAXSIZE], node);
}

void myHashSetFree(MyHashSet *obj) {
    int i;
    List *freeIt;
    List *curIt;
    for (i = 0; i < MAXSIZE; i++) {
        if (obj->hashHead[i] != NULL) {
            freeIt = NULL;
            curIt = obj->hashHead[i];

            while (curIt != NULL) {
                freeIt = curIt;
                curIt = curIt->next;
                free(freeIt);
            }
            obj->hashHead[i] = NULL;
        }
    }
    free(obj);
}


bool hasCycle(struct ListNode *head) {
    struct ListNode *nodeIt = head;
    MyHashSet *myHash = myHashSetCreate();
    while (nodeIt != NULL) {
        if (myHashSetContains(myHash, nodeIt))//判断在不在哈希中
        {
            myHashSetFree(myHash);
            return true;
        } else {
            myHashSetAdd(myHash, nodeIt);
        }
        nodeIt = nodeIt->next;
    }
    myHashSetFree(myHash);
    return false;
}


int main(int argc, char const *argv[]) {
    // 构建一个链表
    struct ListNode headNode;
    struct ListNode node2;
    struct ListNode node3;
    struct ListNode node4;

    headNode.val = 3;
    headNode.next = &node2;

    node2.val = 2;
    node2.next = &node3;

    node3.val = 0;
    node3.next = &node4;

    node4.val = -4;
    node4.next = &node2;

    bool res = hasCycle(&headNode);

    printf("res:%d \n", res);

    return 0;
}
