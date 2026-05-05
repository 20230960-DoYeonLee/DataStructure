#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        printf("%d -> ", curr->data);
        curr = curr->next;
    }
    printf("NULL\n");
}

int searchValue1(Node* head, int val) {
    Node* curr = head;
    int pos = 1;
    while (curr != NULL) {
        if (curr->data == val) return pos;
        curr = curr->next;
        pos++;
    }
    return -1;
}

void searchValue2(Node* head, int val) {
    Node* prev = NULL;
    Node* curr = head;
    while (curr != NULL) {
        if (curr->data == val) {
            if (prev != NULL) printf("앞 노드: %d, ", prev->data);
            else printf("앞 노드 없음, ");

            if (curr->next != NULL) printf("뒤 노드: %d\n", curr->next->data);
            else printf("뒤 노드 없음\n");
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    printf("값을 찾지 못했습니다.\n");
}

void freeList(Node* head) {
    Node* curr = head;
    Node* nextNode;
    while (curr != NULL) {
        nextNode = curr->next;
        free(curr);
        curr = nextNode;
    }
}

int main() {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = 10;
    head->next = (Node*)malloc(sizeof(Node));
    head->next->data = 20;
    head->next->next = (Node*)malloc(sizeof(Node));
    head->next->next->data = 30;
    head->next->next->next = NULL;

    printList(head);

    int pos = searchValue1(head, 20);
    if (pos != -1) printf("위치: %d\n", pos);

    searchValue2(head, 20);

    freeList(head);

    return 0;
}