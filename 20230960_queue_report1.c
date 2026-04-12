#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define SIZE 30 //큐의 최대 크기를 30으로 정함 (0~29) << 이 값은 define으로 정의했기에 고정임.

typedef struct {
    int data[SIZE]; //define으로 정의한 크기가 30인 배열 data 생성
    int front; //data 배열의 맨 앞번호 칸 즉, 현재 배열 내부에서 가장 먼저 들어간 값의 칸을 가르키는 인덱스
    int rear; //data 배열의 맨 뒷번호 칸 즉, 현재 배열 내부에서  가장 나중에 들어간 값의 칸을 가르키는 인덱스
} LinearQueue;

void initQueue(LinearQueue* q) {
    q->front = 0;
    q->rear = -1;
} //queue 초기화 함수로, 큐의 시작위치(front)를 0으로 설정하고 마지막 칸(rear)을 -1으로 설정하여 "아직 아무 데이터도 들어가있지 않다"를 나타냄.

bool isEmpty(LinearQueue* q) {
    return q->rear < q->front;
} // data 배열이 비어있는지 검사하는 코드 

//맨 뒷칸(rear)이 맨 앞칸(front)보다 작으면 큐는 비어있다 -> true(1)을 반환함
//* ex)
// 
// 1)  rear= -1 / front = 0 일경우
// rear < front  >>  -1 < 0  >>  true  >> 큐는 비어있음
// 
// 
// 2)  rear = 0 / front = 0
// rear < front  >>  0 < 0  >>  false  >> 큐는 비어있지않음
// 
// *//

bool isFull(LinearQueue* q) {
    return q->rear == SIZE - 1;
} // data 배열이 가득 차있는지 검사하는 코드 
//큐가 가득 차 있으면 true(1), 아니면 false(0)을 반환


// 큐 데이터 출력 함수
void display(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("\n[알림] 현재 큐가 비어 있습니다.\n");
        return;
    } //큐가 비어있는지 검사하고 비어있다면 프린트
    printf("\n현재 큐 데이터: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("[%d] ", q->data[i]);
    } //현재 data 배열 내부의 모든 데이터를 출력하는 반복문, i=front이고 i가 rear(맨끝칸)보다 작거나 같을경우까지
    printf("\n");
}

bool enqueue(LinearQueue* q, int value) {
    if (isFull(q)) {
        printf("\n[오류] 큐가 가득 찼습니다. (최대 30개)\n");
        return false; //큐가 가득차 삽입에 실패했으므로 false 반환
    } //배열 칸이 가득 찼을경우 오류 출력 (isFull이 ture(1)일 경우)
    q->rear++; //배열 안에 값을 넣기 위하여 제일 위의 칸 늘림
    q->data[q->rear] = value; //data배열에 위에서 늘린 rear칸에 value값을 넣음
    printf("\n[성공] %d 삽입 완료.\n", value);
    return true; ///큐에 삽입을 성공했으므로 true 반환
}

int dequeue(LinearQueue* q) {
    if (isEmpty(q)) {
        printf("\n[오류] 삭제할 데이터가 없습니다.\n");
        return -1;
    }
    int value = q->data[q->front]; //front칸의 값을 value에 저장
    q->front++; //front값을 삭제했으니 다음 칸을 front칸으로 지정

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
            while (getchar() != '\n'); // 입력 버퍼 비우기 (무한 루프 방지)
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
