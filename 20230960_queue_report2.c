#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10   // 최대 작업 대기열 크기
#define MAX_PAGES 50  // 허용 최대 페이지 수

// 프린터 작업 구조체
typedef struct {
    char documentName[50];  // 문서 이름
    int numPages;           // 페이지 수
} PrintJob;

// 큐 구조체 (원형 큐)
typedef struct {
    PrintJob list[SIZE];  // 작업 저장 배열
    int front;             // 첫 번째 요소 위치
    int rear;              // 마지막 요소 다음 위치
} PrintQueue;


// 큐 초기화
void initQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
}

// 큐가 비어있는지 확인
bool isEmpty(PrintQueue* q) {
    return q->front == q->rear;
}

// 큐가 가득 찼는지 확인
bool isFull(PrintQueue* q) {
    return (q->rear + 1) % SIZE == q->front;
}

// 작업 추가 (조건 추가됨)
bool enqueue(PrintQueue* q, char* documentName, int numPages) {

    //조건 1: 페이지 수 제한
    if (numPages > MAX_PAGES) {
        printf("페이지 수가 50장을 초과하여 작업이 거부되었습니다.\n");
        return false;
    }

    //조건 2: 큐가 가득 찬 경우
    if (isFull(q)) {
        printf("대기열이 가득 찼습니다. 작업을 추가할 수 없습니다.\n");
        return false;
    }

    // 정상 추가
    strcpy(q->list[q->rear].documentName, documentName);
    q->list[q->rear].numPages = numPages;

    // rear 이동 (원형 큐)
    q->rear = (q->rear + 1) % SIZE;

    printf("작업 '%s' (%d 페이지)가 추가되었습니다.\n", documentName, numPages);
    return true;
}

// 작업 제거 (dequeue)
PrintJob dequeue(PrintQueue* q) {

    // 큐가 비어있을 경우
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        PrintJob emptyJob = { "", 0 };
        return emptyJob;
    }

    // front 위치의 작업 꺼냄
    PrintJob job = q->list[q->front];

    // front 이동
    q->front = (q->front + 1) % SIZE;

    return job;
}

// 작업 취소 함수
void cancelJob(PrintQueue* q, char* documentName) {

    // 큐가 비어있는 경우
    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    int i = q->front;
    int found = 0;

    //해당 문서 탐색
    while (i != q->rear) {
        if (strcmp(q->list[i].documentName, documentName) == 0) {
            found = 1;
            break;
        }
        i = (i + 1) % SIZE;
    }

    //찾지 못한 경우
    if (!found) {
        printf("해당 문서가 없습니다.\n");
        return;
    }

    //삭제 후 한 칸씩 앞으로 당김
    while (i != q->rear) {
        int next = (i + 1) % SIZE;
        q->list[i] = q->list[next];
        i = next;
    }

    // rear 한 칸 뒤로 이동
    q->rear = (q->rear - 1 + SIZE) % SIZE;

    printf("작업 '%s'이(가) 취소되었습니다.\n", documentName);
}

//전체 대기열 초기화
void clearQueue(PrintQueue* q) {
    q->front = 0;
    q->rear = 0;
    printf("대기열 초기화\n");
}

// 큐 상태 출력
void printQueue(PrintQueue* q) {

    if (isEmpty(q)) {
        printf("대기열이 비어 있습니다.\n");
        return;
    }

    printf("현재 대기 중인 작업:\n");

    int i = q->front;

    // front부터 rear까지 순회
    while (i != q->rear) {
        printf("- %s (%d 페이지)\n",
            q->list[i].documentName,
            q->list[i].numPages);

        i = (i + 1) % SIZE;
    }
}

// ======================================
// 메인 함수
int main() {

    PrintQueue q;
    initQueue(&q);

    int choice;
    char documentName[50];
    int numPages;

    while (true) {

        printf("\n===== 메뉴 =====\n");
        printf("1. 작업 추가\n");
        printf("2. 작업 처리\n");
        printf("3. 대기열 출력\n");
        printf("4. 작업 취소\n");
        printf("5. 대기열 초기화\n");
        printf("6. 종료\n");
        printf("선택: ");

        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("문서 이름: ");
            scanf("%s", documentName);

            printf("페이지 수: ");
            scanf("%d", &numPages);

            enqueue(&q, documentName, numPages);
            break;

        case 2: {
            PrintJob job = dequeue(&q);

            if (strlen(job.documentName) > 0) {
                printf("작업 '%s' (%d 페이지) 처리 중...\n",
                    job.documentName,
                    job.numPages);
            }
            break;
        }

        case 3:
            printQueue(&q);
            break;

        case 4:
            printf("취소할 문서 이름: ");
            scanf("%s", documentName);
            cancelJob(&q, documentName);
            break;

        case 5:
            clearQueue(&q);
            break;

        case 6:
            printf("프로그램 종료\n");
            return 0;

        default:
            printf("잘못된 입력입니다.\n");
        }
    }
}