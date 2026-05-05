#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char name[20];
    char phone[20];
    struct Node* next;
} Node;

Node* insertContact(Node* head) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return head;

    printf("이름 입력: ");
    scanf("%s", newNode->name);
    printf("번호 입력: ");
    scanf("%s", newNode->phone);
    newNode->next = NULL;

    if (head == NULL) {
        printf("\n=> [%s] 추가 완료\n", newNode->name);
        return newNode;
    }

    Node* curr = head;
    while (curr->next != NULL) curr = curr->next;
    curr->next = newNode;

    printf("\n=> [%s] 추가 완료\n", newNode->name);
    return head;
}

void searchContact(Node* head) {
    char name[20];
    printf("검색할 이름 입력: ");
    scanf("%s", name);

    Node* curr = head;
    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            printf("[%s] 번호: %s\n", curr->name, curr->phone);
            return;
        }
        curr = curr->next;
    }
    printf("찾는 이름이 없습니다.\n");
}

Node* deleteContact(Node* head) {
    if (head == NULL) {
        printf("전화번호부가 비어있습니다.\n");
        return NULL;
    }

    char name[20];
    printf("삭제할 이름 입력: ");
    scanf("%s", name);

    Node* curr = head;
    Node* prev = NULL;

    while (curr != NULL) {
        if (strcmp(curr->name, name) == 0) {
            Node* nextNode = curr->next;

            if (prev == NULL) {
                head = nextNode;
            }
            else {
                prev->next = nextNode;
            }

            printf("\n=> [%s] 삭제 완료\n", curr->name);
            free(curr);
            return head;
        }
        prev = curr;
        curr = curr->next;
    }

    printf("삭제할 이름이 없습니다.\n");
    return head;
}

void printAll(Node* head) {
    Node* curr = head;
    if (curr == NULL) {
        printf("\n전화번호부가 비어있습니다.\n");
        return;
    }
    printf("\n--- 리스트 ---\n");
    while (curr != NULL) {
        printf("이름: %s | 번호: %s\n", curr->name, curr->phone);
        curr = curr->next;
    }
    printf("--------------\n");
}

void freeList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        Node* next = curr->next;
        free(curr);
        curr = next;
    }
}

int main() {
    Node* head = NULL;
    int menu;

    while (1) {
        printf("\n1.추가 2.검색 3.삭제 4.출력 5.종료\n선택: ");
        if (scanf("%d", &menu) != 1) {
            while (getchar() != '\n');
            continue;
        }

        if (menu == 1) head = insertContact(head);
        else if (menu == 2) searchContact(head);
        else if (menu == 3) head = deleteContact(head);
        else if (menu == 4) printAll(head);
        else if (menu == 5) break;
        else printf("잘못된 입력입니다.\n");
    }

    freeList(head);
    return 0;
}