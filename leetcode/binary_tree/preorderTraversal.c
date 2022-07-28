#include <stdio.h>
#include <stdlib.h>

/**
 * @brief  前序遍历
 *

 */

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TNode;

void preOrder(TNode *root, int *res, int *resSize) {
    if (root == NULL) {
        return;
    }
    printf("%d \n", root->val);
    res[(*resSize)++] = root->val;
    preOrder(root->left, res, resSize);
    preOrder(root->right, res, resSize);
}
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
// 前序遍历（根左右）： 先从根节点出发，    根节点-> 左节点 -> 右节点
// 中序遍历（左根右）： 先从最左子节点出发， 左边节点 -> 根节点 -> 右节点
// 后序遍历（左右根）： 先从最左节点出发， 左边节点 -> 右节点 -> 根节点
int *preorderTraversal(struct TreeNode *root, int *returnSize) {
    // 根左右， 先遍历
    int *res = malloc(2000);
    *returnSize = 0;
    preOrder(root, res, returnSize);
    return returnSize;
}

void preorder(struct TreeNode *root, int *res, int *resSize) {
    if (root == NULL) {
        return;
    }
    res[(*resSize)++] = root->val;
    preorder(root->left, res, resSize);
    preorder(root->right, res, resSize);
}

int *preorderTraversal2(struct TreeNode *root, int *returnSize) {
    int *res = malloc(sizeof(int) * 2000);
    preorder(root, res, returnSize);
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

    int *returnSize = 0;
    preorderTraversal2(&treeNode1, returnSize);

    return 0;
}