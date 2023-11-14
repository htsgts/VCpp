#pragma once

class y_stack {
public:
    y_stack();
    ~y_stack();

    void push(int num);
    int pop();

private:
    int* data;  // int 형 데이터를 저장하는 배열을 위한 포인터
    int top;    // 스택의 top 인덱스
    const int MAX_SIZE;  // 스택의 최대 크기
};
