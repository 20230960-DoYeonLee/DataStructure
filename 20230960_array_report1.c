#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 함수 선언
double calculateAverage(int scores[], int size);
int getStudentScore(int scores[], int size, int studentNumber);
void printScore(int scores[], int size, double average, int option);

int main() {
    int scores[30]; // 30명의 학생 성적 저장
    int studentNumber;
    double average;

    // 난수 생성 초기화
    srand(time(0));

    // 성적 데이터 초기화
    for (int i = 0; i < 30; i++) {
        scores[i] = rand() % 101; // 0 ~ 100 사이의 난수 생성
    }

    // 평균 계산
    average = calculateAverage(scores, 30);
    printf("Class average score: %.2f\n", average);

    // 특정 학생 점수 검색
    printf("Enter student number (1 ~ 30): ");
    scanf_s("%d", &studentNumber);

    int score = getStudentScore(scores, 30, studentNumber);
    if (score != -1) {
        printf("Student %d score: %d\n", studentNumber, score);
    }
    else {
        printf("Invalid student number.\n");
    }

    printScore(scores, 30, average, 0);
    printScore(scores, 30, average, 1);
    printScore(scores, 30, average, 2);

    return 0;
}

// 평균 계산 함수
double calculateAverage(int scores[], int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += scores[i];
    }
    return sum / (double)size;
}

// 특정 학생 점수 검색 함수
int getStudentScore(int scores[], int size, int studentNumber) {
    if (studentNumber >= 1 && studentNumber <= size) {
       return scores[studentNumber - 1];
    }
    else {
        return -1;
    }
}

// 학생 정보 출력 함수
void printScore(int scores[], int size, double average, int option) {
    switch (option) {
    case 0:
        for (int i = 0; i < size; i++) {
            printf("Student number: %d, Score: %d\n", i + 1, scores[i]);
        }
        break;
    case 1:
        printf("Students above or equal to average\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] >= average)
                printf("Student number: %d, Score: %d\n", i + 1, scores[i]);
        }
        break;

    case 2:
        printf("Students below average\n");
        for (int i = 0; i < size; i++) {
            if (scores[i] < average)
                printf("Student number: %d, Score: %d\n", i + 1, scores[i]);
        }
        break;

    default:
        printf("Invalid option.\n");
        break;
    }
}