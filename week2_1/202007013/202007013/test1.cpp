#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main()
{
	char input;
	char ch;

	printf("202007013\n");
	printf("����������\n");
	printf("Application\n");


	while (1) {
		printf("command>");
		input = _getch(); // Ű �Է��� ������
		scanf("\n%c", &input);
		if (input == 'p') {
			printf("���� ������ �̳� ���ϴ� �л��̴�.\n");
		}
		else if (input == 'f') {
			printf("���� ������ �ʹ� ��̴�.\n");
		}
		else if (input == 'j') {
			printf("������ ���� �� ���ּ���.\n");
		}
		
			if (input == 27) { // Esc Ű�� ASCII �ڵ�� 27
				printf("���α׷��� �����մϴ�.\n");
				break; // ���� ����
			}
	}
	return 0;
}