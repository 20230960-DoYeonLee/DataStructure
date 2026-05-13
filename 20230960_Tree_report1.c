#include <stdio.h>
#include <stdlib.h>

//트리 노드함수
typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

//노드 생성함수
TreeNode* createNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

//순회함수
void preorder(TreeNode* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void inorder(TreeNode* root) {
    if (root) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void postorder(TreeNode* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

//트리 분석함수
int getHeight(TreeNode* root) {
    if (root == NULL) return -1; //리프 노드 아래를 -1로 해야 앳지 기준 높이 2가 나옴
    int leftHeight = getHeight(root->left);
    int rightHeight = getHeight(root->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

int countNodes(TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int countLeaves(TreeNode* root) {
    if (root == NULL) return 0;
    if (root->left == NULL && root->right == NULL) return 1;
    return countLeaves(root->left) + countLeaves(root->right);
}

//합계
int getSum(TreeNode* root) {
    if (root == NULL) return 0;
    return root->data + getSum(root->left) + getSum(root->right);
}

int getMax(TreeNode* root) {//최댓값
    if (root == NULL) return -1;
    int max = root->data;
    int leftMax = getMax(root->left);
    int rightMax = getMax(root->right);

    if (leftMax > max) max = leftMax;
    if (rightMax > max) max = rightMax;
    return max;
}

void searchRange(TreeNode* root, int min, int max) {//범위탐색
    if (root == NULL) return;
    if (root->data >= min && root->data <= max) {
        printf("%d ", root->data);
    }
    searchRange(root->left, min, max);
    searchRange(root->right, min, max);
}


void freeTree(TreeNode* root) { // 메모리 해제
    if (root == NULL) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    TreeNode* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(20);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(15);
    root->right->right = createNode(25);

    // 순회 출력
    printf("전위 순회: ");
    preorder(root);
    printf("\n");

    printf("중위 순회: ");
    inorder(root);
    printf("\n");

    printf("후위 순회: ");
    postorder(root);
    printf("\n\n");

    // 분석 출력
    printf("트리 높이: %d\n", getHeight(root));
    printf("전체 노드 수: %d\n", countNodes(root));
    printf("리프 노드 수: %d\n", countLeaves(root));

    printf("노드 값 총합: %d\n", getSum(root));
    printf("최댓값: %d\n\n", getMax(root));

    // 범위 탐색
    printf("값이 6 이상 20 이하인 노드: ");
    searchRange(root, 6, 20);
    printf("\n");

    freeTree(root);
    return 0;
}
