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

/**
 *  方法一： 慢指针和快指针 ， 只要有相遇就有环
 * @param head
 * @return
 */
bool hasCycle1(struct ListNode *head) {
    struct ListNode *slow, *fast;

    if (head == NULL || head->next == NULL) return false;

//    while (head != NULL) {
//        printf("%d \n", head->val);
//        head = head->next;
//        printf("%p \n", head);
//    }

    slow = head;
    fast = head->next;
    while ((slow != fast)) {
        if ( (fast == NULL || fast->next == NULL)) {
            return false;
        }
        slow = slow->next;
        fast = fast->next->next;
    }

    return true;
}


struct hashTable {
    struct ListNode* key;
    UT_hash_handle hh;
};

struct hashTable* hashtable;

struct hashTable* find(struct ListNode* ikey) {
    struct hashTable* tmp;
    HASH_FIND_PTR(hashtable, &ikey, tmp);
    return tmp;
}

void insert(struct ListNode* ikey) {
    struct hashTable* tmp = malloc(sizeof(struct hashTable));
    tmp->key = ikey;
    HASH_ADD_PTR(hashtable, key, tmp);
}

bool hasCycle(struct ListNode* head) {
    hashtable = NULL;
    while (head != NULL) {
        if (find(head) != NULL) {
            return true;
        }
        insert(head);
        head = head->next;
    }
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
