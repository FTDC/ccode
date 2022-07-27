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

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node;

/**
 * @brief  对比左右节点是否对称
 *
 * @param left
 * @param right
 * @return true
 * @return false
 */
bool compare(Node *left, Node *right) {
    if (left == NULL && right == NULL)
        return true;
    if (left == NULL || right == NULL)
        return false;
    if (left->val != right->val)
        return false;

    // 对比边左边和右边   右边和左边
    return compare(left->left, right->right) && compare(left->right, right->left);
}

/**
 * @brief  判断是否对称
 *
 * @param root
 * @return true
 * @return false
 */
bool isSymmetric(struct TreeNode *root) {
    if (root == NULL) {
        return true;
    }
    // 从根节点出发
    //   printf("left:%d , right:%d \n", root->left->val, root->right->val);
    if (compare(root->left, root->right)) {
        return true;
    }
    return false;
}

int main(int argc, char const *argv[]) {

    // 先声明一个二叉树
    Node treeNode1;
    Node treeNode2;
    Node treeNode3;
    Node treeNode4;
    Node treeNode5;

    treeNode1.val = 1;
    treeNode1.left = &treeNode2;
    treeNode1.right = &treeNode2;

    treeNode2.val = 2;
    treeNode2.left = NULL;
    treeNode2.right = &treeNode3;

    treeNode3.val = 3;
    treeNode3.left = NULL;
    treeNode3.right = NULL;

    //   treeNode4.val = 4;
    //   treeNode4.left = NULL;
    //   treeNode4.right = NULL;

    //   treeNode5.val = 5;
    //   treeNode5.left = NULL;
    //   treeNode5.right = NULL;

    bool res = isSymmetric(&treeNode1);

    printf("%d \n", res);

    return 0;
}