#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
} Node;

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2) {
  struct ListNode *ret, *temp;
  // 临时变量
  ret = malloc(sizeof(struct ListNode)); // ret第一个是空节点🍉

  temp = ret;

  /*
    两个链表中都没有遍历完时，继续循环，如果其中有一个结束了就跳出循环。
    剩下的链表可以直接接在已经排好的有序链表后，因为两个链表都是升序的，如果有一个链表遍历结束说明那个链表已经全部排序好了
    */
  while (list1 && list2) {
    if (list1->val < list2->val) {
      temp->next = list1;
      temp = list1;
      list1 = list1->next;
    } else {
      temp->next = list2;
      temp = list2;
      list2 = list2->next;
    }
  }
  if (list1) {
    //如果list1不为0说明list1还没有遍历完 ，临时指针继续指向下一个；
    temp->next = list1;
  } else {
    //如果list1=0说明链表1
    //遍历完了，那我们的临时指针就要放在list2的位置，把属于的链表直接接上就行了，因为链表本来就是升序
    temp->next = list2;
  }

  return ret->next; //这里，ret是哨兵，里面存的是
                    // NULL，返回咱们自己设的这个哨兵没意义，所以返回 next
}

int main() {
  // 声明两个链表
  struct ListNode node1;
  struct ListNode node2;
  struct ListNode node3;

  node1.val = 1;
  node1.next = &node2;

  node2.val = 2;
  node2.next = &node3;

  node3.val = 4;
  node3.next = NULL;

  struct ListNode node4;
  struct ListNode node5;
  struct ListNode node6;

  node4.val = 1;
  node4.next = &node5;

  node5.val = 3;
  node5.next = &node6;

  node6.val = 4;
  node6.next = NULL;

  struct ListNode *ret = mergeTwoLists(&node1, &node4);

  while (ret) {
    printf("%d \n", ret->val);
    ret = ret->next;
  }

  return 0;
}