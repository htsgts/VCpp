#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <conio.h>

int main()
{
	char input;
	char ch;

	printf("�������� �ູ�� VC++\n");


	while (1) {
		printf("command>");
		scanf("\n%c", &input);
		if (input == 'q') {
			printf("qwer ȭ����!!\n");
		}
		else if (input == 'w') {
			printf("���� �ʹ� ����.\n");
		}
		else if (input == 'e') {
			printf("���ֺ��� ������ 3���.\n");
		}
		else if (input == 'r') {
			printf("�ູ�մϴ�.\n");
		}
		else {
			printf("�߸��� �Է��Դϴ�.�ٽ��Է��ϼ���.\n");
		}
		input = _getch(); // Ű �Է��� ������
			if (input == 27) { // Esc Ű�� ASCII �ڵ�� 27
				printf("���α׷��� �����մϴ�.\n");
				break; // ���� ����
			}
	}
	return 0;
}