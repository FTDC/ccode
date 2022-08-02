//
// 给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。
//
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief
 */

typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TNode;


// 前序遍历（根左右）： 先从根节点出发，    根节点-> 左节点 -> 右节点
// 中序遍历（左根右）： 先从最左子节点出发， 左边节点 -> 根节点 -> 右节点
// 后序遍历（左右根）： 先从最左节点出发， 左边节点 -> 右节点 -> 根节点


struct TreeNode *invertTree(struct TreeNode *root) {

    if (root == NULL) {
        return NULL;
    }
    struct TreeNode *left = invertTree(root->left);
    struct TreeNode *right = invertTree(root->right);
    root->right = left;
    root->left = right;

    return root;
}


int main(int argc, char const *argv[]) {

    // 先声明一个二叉树
    TNode treeNode1;
    TNode treeNode2;
    TNode treeNode3;

    treeNode1.val = 1;
    treeNode1.left = NULL;
    treeNode1.right = NULL;

    treeNode2.val = 2;
    treeNode2.left = &treeNode1;
    treeNode2.right = &treeNode3;

    treeNode3.val = 3;
    treeNode3.left = NULL;
    treeNode3.right = NULL;

    struct TreeNode *res = invertTree(&treeNode2);

    printf("int::%d \n", res->left->val);


    return 0;
}