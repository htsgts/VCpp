#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
    char input_sequence[] = "↓→a"; // 원하는 입력 시퀀스
    char input_buffer[4] = { 0 }; // 입력 버퍼 초기화
    int input_index = 0; // 입력 버퍼 인덱스
    int escape_pressed = 0; // ESC 키 누름 여부

    printf("↓→a 순서로 입력하면 '아도겐! =o' 출력됩니다. 종료하려면 ESC 키를 누르세요.\n");

    while (!escape_pressed) {
        if (_kbhit()) { // 키 입력 확인
            char key = _getch(); // 입력된 키 가져오기

            // 입력 버퍼에 키 추가
            input_buffer[input_index] = key;
            input_index = (input_index + 1) % 4;

            if (input_buffer[input_index] == 'a' &&
                input_buffer[(input_index + 3) % 4] == '↓' &&
                input_buffer[(input_index + 2) % 4] == '→') {
                printf("아도겐! =o\n");
            }

            if (key == 27) { // ESC 키 누름
                escape_pressed = 1;
            }
        }

        Sleep(300); // 300ms 대기
    }

    return 0;
}