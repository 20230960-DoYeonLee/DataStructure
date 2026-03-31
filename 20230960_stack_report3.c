#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int data[MAX];
    int top;
} Stack;

void initStack(Stack* s) { s->top = -1; }
int isEmpty(Stack* s) { return s->top == -1; }

void push(Stack* s, int value) {
    s->data[++(s->top)] = value;
}

int pop(Stack* s) {
    if (isEmpty(s)) return 0;
    return s->data[(s->top)--];
}

int peek(Stack* s) {
    if (isEmpty(s)) return 0;
    return s->data[s->top];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    Stack s;
    initStack(&s);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isdigit(ch)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' ';
            i--;
        }
        else if (ch == '(') {
            push(&s, ch);
        }
        else if (ch == ')') {
            while (!isEmpty(&s) && peek(&s) != '(') {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            pop(&s);
        }
        else { 
            while (!isEmpty(&s) && precedence(peek(&s)) >= precedence(ch)) {
                postfix[j++] = pop(&s);
                postfix[j++] = ' ';
            }
            push(&s, ch);
        }
    }

    while (!isEmpty(&s)) {
        postfix[j++] = pop(&s);
        postfix[j++] = ' ';
    }

    postfix[j] = '\0';
}

int evaluatePostfix(char* postfix) {
    Stack s;
    initStack(&s);

    for (int i = 0; postfix[i] != '\0'; i++) {

        if (isdigit(postfix[i])) {
            int num = 0;

            while (isdigit(postfix[i])) {
                num = num * 10 + (postfix[i] - '0');
                i++;
            }

            push(&s, num);
        }
        else if (postfix[i] == ' ') {
            continue;
        }
        else { 
            int b = pop(&s);
            int a = pop(&s);
            int result;

            switch (postfix[i]) {
            case '+': result = a + b; break;
            case '-': result = a - b; break;
            case '*': result = a * b; break;
            case '/': result = a / b; break;
            default:
                printf("오류: 잘못된 연산자\n");
                exit(1);
            }

            push(&s, result);
        }
    }

    return pop(&s);
}


int main(void) {
    char infix[MAX];
    char postfix[MAX];
    int result;

    printf("중위표기식 입력: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    result = evaluatePostfix(postfix);

    printf("후위표기식: %s\n", postfix);
    printf("계산 결과: %d\n", result);

    return 0;
}