#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main()
{
	char input;
	char ch;

	printf("202007013\n");
	printf("이은석님의\n");
	printf("Application\n");


	while (1) {
		printf("command>");
		input = _getch(); // 키 입력을 가져옴
		scanf("\n%c", &input);
		if (input == 'p') {
			printf("나는 과제를 겁나 잘하는 학생이다.\n");
		}
		else if (input == 'f') {
			printf("나는 과제가 너무 즐겁다.\n");
		}
		else if (input == 'j') {
			printf("교수님 과제 더 내주세요.\n");
		}
		
			if (input == 27) { // Esc 키의 ASCII 코드는 27
				printf("프로그램을 종료합니다.\n");
				break; // 루프 종료
			}
	}
	return 0;
}