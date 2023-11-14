#include "yuhan_stack.h"
#include <iostream> 

void y_stack::push(int num) {
    if (top >= MAX_SIZE - 1) {
        // 스택이 가득 찼을 때의 처리
        // 여기서는 간단히 메시지를 출력하고 종료
        std::cout << "Stack overflow! Cannot push more elements." << std::endl;
        return;
    }
    data[++top] = num;  // top을 증가시키고 값을 저장
}

int y_stack::pop() {
    if (top < 0) {
        // 스택이 비어 있을 때의 처리
        // 여기서는 간단히 -1을 반환하고 종료
        std::cout << "Stack underflow! Cannot pop from an empty stack." << std::endl;
        return -1;
    }
    return data[top--];  // top을 감소시키고 값을 반환
}
