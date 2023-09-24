#include <stdio.h>
#include <conio.h>
#include <windows.h>

int main() {
    char input_sequence[] = "���a"; // ���ϴ� �Է� ������
    char input_buffer[4] = { 0 }; // �Է� ���� �ʱ�ȭ
    int input_index = 0; // �Է� ���� �ε���
    int escape_pressed = 0; // ESC Ű ���� ����

    printf("���a ������ �Է��ϸ� '�Ƶ���! =o' ��µ˴ϴ�. �����Ϸ��� ESC Ű�� ��������.\n");

    while (!escape_pressed) {
        if (_kbhit()) { // Ű �Է� Ȯ��
            char key = _getch(); // �Էµ� Ű ��������

            // �Է� ���ۿ� Ű �߰�
            input_buffer[input_index] = key;
            input_index = (input_index + 1) % 4;

            if (input_buffer[input_index] == 'a' &&
                input_buffer[(input_index + 3) % 4] == '��' &&
                input_buffer[(input_index + 2) % 4] == '��') {
                printf("�Ƶ���! =o\n");
            }

            if (key == 27) { // ESC Ű ����
                escape_pressed = 1;
            }
        }

        Sleep(300); // 300ms ���
    }

    return 0;
}