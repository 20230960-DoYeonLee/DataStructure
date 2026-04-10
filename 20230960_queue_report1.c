#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define SIZE 30

typedef struct {
    int data[SIZE];
    int front;
    int rear;
} LinearQueue;

void initQueue(LinearQueue* q) {
    q->front = 0;
    q->rear = -1;
}

bool isEmpty(LinearQueue* q) {
    return q->rear < q->front;
}

bool isFull(LinearQueue* q) {
    return q->rear == SIZE - 1;
}

// 큐 데이터 출력 함수
void display(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("\n[알림] 현재 큐가 비어 있습니다.\n");
        return;
    }
    printf("\n현재 큐 데이터: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("[%d] ", q->data[i]);
    }
    printf("\n");
}

bool enqueue(LinearQueue* q, int value) {
    if (isFull(q)) {
        printf("\n[오류] 큐가 가득 찼습니다. (최대 30개)\n");
        return false;
    }
    q->rear++;
    q->data[q->rear] = value;
    printf("\n[성공] %d 삽입 완료.\n", value);
    return true;
}

int dequeue(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("\n[오류] 삭제할 데이터가 없습니다.\n");
        return -1;
    }
    int value = q->data[q->front];
    q->front++;

    // 큐가 비었을 때 초기화 (사진의 2번 조건)
    if (isEmpty(q)) {
        initQueue(q);
        printf("\n[안내] 모든 데이터를 삭제하여 큐를 초기화했습니다.\n");
    }
    return value;
}

int main() {
    LinearQueue q;
    initQueue(&q);
    int choice, value;

    while (1) {
        printf("\n========== QUEUE MENU ==========\n");
        printf("1. 삽입 (Enqueue)\n");
        printf("2. 삭제 (Dequeue)\n");
        printf("3. 큐 데이터 출력\n");
        printf("4. 종료 (Exit)\n");
        printf("선택: ");

        // scanf의 반환값을 확인하여 숫자가 아닌 입력 처리
        if (scanf("%d", &choice) != 1) {
            printf("\n[오류] 숫자만 입력 가능합니다!\n");
            while (getchar() != '\n'); // 입력 버퍼 비우기 (무한 루프 방지 핵심)
            continue;
        }

        switch (choice) {
        case 1:
            printf("삽입할 숫자 입력: ");
            if (scanf("%d", &value) != 1) {
                printf("\n[오류] 올바른 숫자를 입력하세요.\n");
                while (getchar() != '\n');
            }
            else {
                enqueue(&q, value);
            }
            break;
        case 2:
            value = dequeue(&q);
            if (value != -1) {
                printf("\n[결과] 삭제된 데이터: %d\n", value);
            }
            break;
        case 3:
            display(&q);
            break;
        case 4:
            printf("\n프로그램을 종료합니다.\n");
            return 0;
        default:
            printf("\n[오류] 1~4 사이의 번호를 입력해주세요.\n");
        }
    }
    return 0;
}