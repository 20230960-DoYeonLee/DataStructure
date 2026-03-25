#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[101]; // 입력 문자열 (최대 100자)
    char* stack; // 스택
    int top = -1;
    int length;

    printf("문자열 입력: "); //문자열 입력
    fgets(str, sizeof(str), stdin); //scanf는 띄여쓰기 불가

    str[strcspn(str, "\n")] = '\0'; //개행 제거 (안하면 \n도 한칸을 먹어서 문자열을 99까지밖에 못씀)

    length = strlen(str);

    stack = (char*)malloc(sizeof(char) * length); //스택 메모리 동적 할당

    for (int i = 0; i < length; i++) {
        stack[++top] = str[i];
    }

    printf("거꾸로 출력: "); //pop 하면서 출력 (역순으로)
    while (top != -1) {
        printf("%c", stack[top--]);
    }

    printf("\n");

    free(stack); // 메모리 해제

    return 0;
}