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


// 前序遍历（根左右）： 先从根节点出发，    根节点-> 左节点 -> 右节点
// 中序遍历（左根右）： 先从最左子节点出发， 左边节点 -> 根节点 -> 右节点
// 后序遍历（左右根）： 先从最左节点出发， 左边节点 -> 右节点 -> 根节点


struct TreeNode *mergeNode(struct TreeNode *node1, struct TreeNode *node2){
    struct TreeNode *node;
    if (node1->left && node2->left){
        node->val = node1->val + node2->val;
    }else if (node1->left){
        node->left = node1->left;
    }else if(node1->right){
        node->right = node2->right;
    }

    return node;
}

struct TreeNode* mergeTrees(struct TreeNode* root1, struct TreeNode* root2){

    if (root1 == NULL) {
        return root2;
    }
    if (root2 == NULL) {
        return root1;
    }
    struct TreeNode* merged = malloc(sizeof(struct TreeNode));
    merged->val = root1->val + root2->val;
    merged->left = mergeTrees(root1->left, root2->left);
    merged->right = mergeTrees(root1->right, root2->right);
    return merged;

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


    TNode treeNode4;
    TNode treeNode5;
    TNode treeNode6;

    treeNode4.val = 4;
    treeNode4.left = &treeNode5;
    treeNode4.right = &treeNode6;

    treeNode5.val = 5;
    treeNode5.left = NULL;
    treeNode5.right = NULL;

    treeNode6.val = 6;
    treeNode6.left = NULL;
    treeNode6.right = NULL;

    int returnSize = 0;
    TNode *res = mergeTrees(&treeNode1, &treeNode4);

    printf("int::%d \n", returnSize);
    for (int i = 0; i < returnSize; ++i) {
        printf("%d \n", res[i]);
    }

    return 0;
}