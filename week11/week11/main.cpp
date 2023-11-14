#include <stdio.h>
#include <stdbool.h>

#define MAX_STACK_SIZE 100

int stack[MAX_STACK_SIZE];
int top = -1;

bool IsEmpty() {
    return (top < 0);
}

bool IsFull() {
    return (top >= MAX_STACK_SIZE - 1);
}

void push(int value) {
    if (IsFull()) {
        printf("스택이 가득 찼습니다.\n");
    }
    else {
        printf("적재: %d\n", value);
        stack[++top] = value;
    }
}

int pop() {
    if (IsEmpty()) {
        printf("스택이 비었습니다.\n");
        return -1; // 스택이 비어 있는 경우 -1로 값을 반환
    }
    else {
        printf("삭제: %d\n", stack[top]);
        return stack[top--];
    }
}

int main() {
    push(3);
    push(5);
    push(12);
    pop();
    pop();
    pop();
    pop();
    push(23);
    push(11);
    pop();

    return 0;
}
