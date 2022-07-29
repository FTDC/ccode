//
// Created by Administrator on 2022/7/29.
//
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief  中序遍历
 *
 */

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TNode;


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 前序遍历（根左右）： 先从根节点出发，    根节点-> 左节点 -> 右节点
// 中序遍历（左根右）： 先从最左子节点出发， 左边节点 -> 根节点 -> 右节点
// 后序遍历（左右根）： 先从最左节点出发， 左边节点 -> 右节点 -> 根节点



void inorder(struct TreeNode *root, int *res, int *returnSize) {
    if (!root) {
        return;
    }

    // 遍历左边的节点
    inorder(root->left, res, returnSize);
    res[(*returnSize)++] = root->val;
    inorder(root->right, res, returnSize);
}

/**
 *  中序遍历  左根右
 * @param root
 * @param returnSize
 * @return
 */
int *inorderTraversal(struct TreeNode *root, int *returnSize) {
    // 存储返回结果
    int *res = malloc(sizeof(int) * 512);
    // 遍历
    inorder(root, res, returnSize);

    return res;

}

int main(int argc, char const *argv[]) {

    // 先声明一个二叉树
    TNode treeNode1;
    TNode treeNode2;
    TNode treeNode3;

    treeNode1.val = 1;
    treeNode1.left = NULL;
    treeNode1.right = &treeNode2;

    treeNode2.val = 2;
    treeNode2.left = &treeNode3;
    treeNode2.right = NULL;

    treeNode3.val = 3;
    treeNode3.left = NULL;
    treeNode3.right = NULL;

    int returnSize = 0;
    int *res = inorderTraversal(&treeNode1, &returnSize);

    printf("int::%d \n", returnSize);
    for (int i = 0; i < returnSize; ++i) {
        printf("%d \n", res[i]);
    }

    return 0;
}