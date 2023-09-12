#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main()
{
	char input;
	char ch;

	printf("이은석의 행복한 VC++\n");


	while (1) {
		printf("command>");
		scanf("\n%c", &input);
		if (input == 'q') {
			printf("qwer 화이팅!!\n");
		}
		else if (input == 'w') {
			printf("과제 너무 좋다.\n");
		}
		else if (input == 'e') {
			printf("담주부터 과제량 3배다.\n");
		}
		else if (input == 'r') {
			printf("행복합니다.\n");
		}
		else {
			printf("잘못된 입력입니다.다시입력하세요.\n");
		}
		input = _getch(); // 키 입력을 가져옴
			if (input == 27) { // Esc 키의 ASCII 코드는 27
				printf("프로그램을 종료합니다.\n");
				break; // 루프 종료
			}
	}
	return 0;
}