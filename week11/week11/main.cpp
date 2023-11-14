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
        printf("������ ���� á���ϴ�.\n");
    }
    else {
        printf("����: %d\n", value);
        stack[++top] = value;
    }
}

int pop() {
    if (IsEmpty()) {
        printf("������ ������ϴ�.\n");
        return -1; // ������ ��� �ִ� ��� -1�� ���� ��ȯ
    }
    else {
        printf("����: %d\n", stack[top]);
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
