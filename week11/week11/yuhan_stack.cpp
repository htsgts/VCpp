#include "yuhan_stack.h"
#include <iostream> 

void y_stack::push(int num) {
    if (top >= MAX_SIZE - 1) {
        // ������ ���� á�� ���� ó��
        // ���⼭�� ������ �޽����� ����ϰ� ����
        std::cout << "Stack overflow! Cannot push more elements." << std::endl;
        return;
    }
    data[++top] = num;  // top�� ������Ű�� ���� ����
}

int y_stack::pop() {
    if (top < 0) {
        // ������ ��� ���� ���� ó��
        // ���⼭�� ������ -1�� ��ȯ�ϰ� ����
        std::cout << "Stack underflow! Cannot pop from an empty stack." << std::endl;
        return -1;
    }
    return data[top--];  // top�� ���ҽ�Ű�� ���� ��ȯ
}
