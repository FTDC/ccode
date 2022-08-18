/**
 * @file
 * @brief 给定一棵二叉树，你需要计算它的直径长度。一棵二叉树的直径长度是任意两个结点路径长度中的最大值。这条路径可能穿过也可能不穿过根结点。
 * @version 0.1
 * @date 2022-07-27
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdbool.h>
#include <stdio.h>
#include <math.h>

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} Node;


/**
 * 递归遍历树的深度
 * @param root
 * @param deep
 */
int depth(struct TreeNode *root, int *deep) {
    if (root == NULL) return 0;
    // 左边节点的长度
    int leftLen = depth(root->left, deep);
    // 右边节点的长度
    int rightLen = depth(root->right, deep);
    *deep = fmax(*deep, leftLen + rightLen + 1);
    return fmax(leftLen, rightLen) + 1;
}

/**
 * @brief  两结点之间的路径长度
 *
 * @param root
 * @return true
 * @return false
 */
int diameterOfBinaryTree(struct TreeNode *root) {
    int deep = 1;
    depth(root, &deep);
    return deep - 1;
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
    treeNode1.right = &treeNode3;

    treeNode2.val = 2;
    treeNode2.left = &treeNode4;
    treeNode2.right = &treeNode5;

    treeNode3.val = 3;
    treeNode3.left = NULL;
    treeNode3.right = NULL;

    treeNode4.val = 4;
    treeNode4.left = NULL;
    treeNode4.right = NULL;

    treeNode5.val = 5;
    treeNode5.left = NULL;
    treeNode5.right = NULL;

    int res = diameterOfBinaryTree(&treeNode1);

    printf("%d \n", res);

    return 0;
}