#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char str[101];
    char stack[101];
    int top = -1;

    printf("문자열을 입력하세요: ");
    fgets(str, sizeof(str), stdin);

    for (int i = 0; str[i] != '\0'; i++) {

        // 여는 괄호 push
        if (str[i] == '(' || str[i] == '{' || str[i] == '[') {
            stack[++top] = str[i];
        } 

        // 닫는 괄호 검사
        else if (str[i] == ')' || str[i] == '}' || str[i] == ']') {

            if (top == -1) {
                printf("유효하지 않은 괄호입니다.\n");
                return 0;
            }

            char open = stack[top--];

            if ((str[i] == ')' && open != '(') ||
                (str[i] == '}' && open != '{') ||
                (str[i] == ']' && open != '[')) {
                printf("유효하지 않은 괄호입니다.\n");
                return 0;
            }
        }
    }

    if (top == -1)
        printf("유효한 괄호입니다.\n");
    else
        printf("유효하지 않은 괄호입니다.\n");

    return 0;
}