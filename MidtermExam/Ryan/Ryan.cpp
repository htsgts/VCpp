#include <Windows.h>
#include <tchar.h>


HWND hRyanButton; // ���̾� ��ư �ڵ�

void DrawRyan(HDC hdc, int x, int y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawRyan(HDC hdc, int x, int y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static POINT dragStart; // �巡�� ���� ���� ����
    static bool isDragging = false;

    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == GetDlgCtrlID(hRyanButton)) {
            // ���̾� ��ư�� ������ ���� ����
            // ���⿡�� ���̾��� ���� �׸��� �Լ� ȣ��
            HDC hdc = GetDC(hWnd);
            DrawRyan(hdc, 100, 100); // ���÷� ��ġ (100, 100)�� �׸�
            ReleaseDC(hWnd, hdc);
        }
        return 0;

    case WM_LBUTTONDOWN:
        if (wParam == MK_LBUTTON) {
            // ���� ���콺 ��ư�� ������ �� �巡�� ����
            dragStart.x = LOWORD(lParam);
            dragStart.y = HIWORD(lParam);
            isDragging = true;
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDragging) {
            // ���� ���콺 ��ư�� �������� �� �巡�� ����
            isDragging = false;
        }
        return 0;

    case WM_MOUSEMOVE:
        if (isDragging) {
            // ���콺 �̵� �߿��� ���̾� �̹����� �׸�
            HDC hdc = GetDC(hWnd);
            int offsetX = LOWORD(lParam) - dragStart.x;
            int offsetY = HIWORD(lParam) - dragStart.y;
            DrawRyan(hdc, 100 + offsetX, 100 + offsetY); // ���÷� ��ġ (100, 100)�� �׸�
            ReleaseDC(hWnd, hdc);
        }
        return 0;

    case WM_CLOSE:
        PostQuitMessage(0);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }

    return 0;
}