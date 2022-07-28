/**
 * @brief 给定一个二叉树，找出其最大深度。
 * @version 0.1
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node;

/**
 *  递归方式计算
 *
 * @param root
 * @return
 */
int maxDepth2(struct TreeNode *root) {
    if (root == NULL)
        return 0;
    return fmax(maxDepth2(root->left), maxDepth2(root->right)) + 1;
}

struct QueNode {
    struct TreeNode *p;
    struct QueNode *next;
};

void init(struct QueNode **p, struct TreeNode *t) {
    (*p) = (struct QueNode *) malloc(sizeof(struct QueNode));
    (*p)->p = t;
    (*p)->next = NULL;
}

int maxDepth(struct TreeNode *root) {
    if (root == NULL) return 0;
    struct QueNode *left, *right;
    init(&left, root);
    right = left;
    int ans = 0, sz = 1, tmp = 0;
    while (left != NULL) {
        tmp = 0;
        while (sz > 0) {
            if (left->p->left != NULL) {
                init(&right->next, left->p->left);
                right = right->next;
                tmp++;
            }
            if (left->p->right != NULL) {
                init(&right->next, left->p->right);
                right = right->next;
                tmp++;
            }
            left = left->next;
            sz--;
        }
        sz += tmp;
        ans++;
    }
    return ans;
}


int main(int argc, char const *argv[]) {
    // 先声明一个二叉树
    struct TreeNode treeNode1;
    struct TreeNode treeNode2;
    struct TreeNode treeNode3;
    struct TreeNode treeNode4;
    struct TreeNode treeNode5;

    treeNode1.val = 3;
    treeNode1.left = &treeNode2;
    treeNode1.right = &treeNode3;

    treeNode2.val = 9;
    treeNode2.left = NULL;
    treeNode2.right = NULL;

    treeNode3.val = 20;
    treeNode3.left = &treeNode4;
    treeNode3.right = &treeNode5;

    treeNode4.val = 15;
    treeNode4.left = NULL;
    treeNode4.right = NULL;

    treeNode5.val = 7;
    treeNode5.left = NULL;
    treeNode5.right = NULL;

    int res = maxDepth(&treeNode1);

    printf("最大深度：%d \n", res);
    return 0;
}