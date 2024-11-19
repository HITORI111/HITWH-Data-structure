#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构体
typedef struct Node {
    char data;
    struct Node* left;
    struct Node* right;
} Node;

// 创建一个新的节点
Node* createNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// 根据先序和中序序列构建二叉树
Node* buildTree(char* preorder, char* inorder, int inorderStart, int inorderEnd, int* preorderIndex) {
    if (inorderStart > inorderEnd) {
        return NULL;
    }

    // 从先序序列中选择当前的节点
    char current = preorder[*preorderIndex];
    (*preorderIndex)++;

    // 创建当前节点
    Node* node = createNode(current);

    // 如果此节点没有子节点（即递归的终止条件）
    if (inorderStart == inorderEnd) {
        return node;
    }

    // 找到当前节点在中序序列中的位置
    int inorderIndex;
    for (inorderIndex = inorderStart; inorderIndex <= inorderEnd; inorderIndex++) {
        if (inorder[inorderIndex] == current) {
            break;
        }
    }

    // 递归构建左子树和右子树
    node->left = buildTree(preorder, inorder, inorderStart, inorderIndex - 1, preorderIndex);
    node->right = buildTree(preorder, inorder, inorderIndex + 1, inorderEnd, preorderIndex);

    return node;
}

// 计算二叉树的深度
int calculateDepth(Node* root) {
    if (root == NULL) {
        return 0;
    }
    int leftDepth = calculateDepth(root->left);
    int rightDepth = calculateDepth(root->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
}

// 计算叶子节点的数量
int countLeaves(Node* root) {
    if (root == NULL) {
        return 0;
    }
    if (root->left == NULL && root->right == NULL) {
        return 1;
    }
    return countLeaves(root->left) + countLeaves(root->right);
}

// 主函数
int main() {
    char preorder[100], inorder[100];
    
    // 读取先序和中序序列
    scanf("%s", preorder);
    scanf("%s", inorder);

    int n = strlen(inorder);  // 节点数量
    int preorderIndex = 0;    // 先序遍历索引

    // 构建二叉树
    Node* root = buildTree(preorder, inorder, 0, n - 1, &preorderIndex);

    // 计算二叉树深度
    int depth = calculateDepth(root);

    // 计算叶子节点数量
    int leafCount = countLeaves(root);

    // 输出结果
    printf("%d\n", depth);
    printf("%d\n", leafCount);

    return 0;
}
