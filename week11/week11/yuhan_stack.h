#pragma once

class y_stack {
public:
    y_stack();
    ~y_stack();

    void push(int num);
    int pop();

private:
    int* data;  // int �� �����͸� �����ϴ� �迭�� ���� ������
    int top;    // ������ top �ε���
    const int MAX_SIZE;  // ������ �ִ� ũ��
};
