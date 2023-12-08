#include <tchar.h>
#include <Windows.h>
#include "yuhanCG.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hBox, hCircle, hBonobono, hRyan, hCube;  // ���ڿ� 5���� ��ư �ڵ�
HCURSOR hCrossCursor; // CROSS Ŀ�� �ڵ�

HBRUSH hBonobonoBrush; // Bonobono�� ������ ������ �귯�� �ڵ�

// Bonobono�� �� ��ġ�� ��Ÿ���� ����
int leftEyeOffset = -20; // ���� ���� 20�ȼ� �Ʒ��� �����ϴ�.
int rightEyeOffset = -20; // ������ ���� 20�ȼ� �Ʒ��� �����ϴ�.

// Bonobono�� �� ���� ��ȯ ����
COLORREF eyeBlackColor = RGB(0, 0, 0);
COLORREF eyeWhiteColor = RGB(255, 255, 255);

void DrawBonobono(HDC hdc) {
    // Bonobono �׸���
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(127, 200, 255)); // �Ǻλ�
    HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 150, 255)); // �Ի�

    // â �߾� ���
    int centerX = 400; // �߾� x ��ǥ
    int centerY = 300; // �߾� y ��ǥ

    // Bonobono �� �׸���
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, centerX - 100, centerY - 100, centerX + 100, centerY + 100);

    // Bonobono ���� �� �׸���
    int leftEyeX = centerX - 95 - leftEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // ���� ����
    Ellipse(hdc, leftEyeX - 4, centerY - 20, leftEyeX + 4, centerY - 6);
    SelectObject(hdc, CreateSolidBrush(eyeWhiteColor)); // �� ����
    Ellipse(hdc, leftEyeX - 2, centerY - 16, leftEyeX + 2, centerY - 10);

    // Bonobono ������ �� �׸���
    int rightEyeX = centerX + 95 + rightEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // ���� ����
    Ellipse(hdc, rightEyeX - 4, centerY - 20, rightEyeX + 4, centerY - 6);
    SelectObject(hdc, CreateSolidBrush(eyeWhiteColor)); // �� ����
    Ellipse(hdc, rightEyeX - 2, centerY - 16, rightEyeX + 2, centerY - 10);

    // Bonobono �� �׸���
    SelectObject(hdc, hMouthBrush);
    Ellipse(hdc, centerX - 11, centerY + 20, centerX + 11, centerY + 60);

    // Bonobono �� �� �׸���
    int noseWidth = 8;
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255))); // �� �ڻ�

    // ���� �� ��
    int leftNoseX = centerX - noseWidth / 2 - leftEyeOffset;
    int leftNoseRadius = 16;
    Ellipse(hdc, leftNoseX - leftNoseRadius - 2, centerY + 20 - leftNoseRadius - 2, leftNoseX + leftNoseRadius + 6, centerY + 20 + leftNoseRadius + 2);

    // ������ �� ��
    int rightNoseX = centerX + noseWidth / 2 + rightEyeOffset;
    int rightNoseRadius = 16;
    Ellipse(hdc, rightNoseX - rightNoseRadius - 6, centerY + 20 - rightNoseRadius - 2, rightNoseX + rightNoseRadius + 2, centerY + 20 + rightNoseRadius + 2);

    // Bonobono ���� �� �׸��� 
    int noseRadius = 12;
    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� �ڻ�
    Ellipse(hdc, centerX - noseRadius - 4, centerY + 25 - noseRadius - 2 - 20, centerX + noseRadius + 4, centerY + 25 + noseRadius + 2 - 20);

    // ���� ���� �� �׸���
    int leftdownMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftdownMustacheY1 = centerY + 40;
    int leftdownMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftdownMustacheY2 = centerY + 25;

    // ���� ���� �Ʒ� �׸���
    int leftupMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftupMustacheY1 = centerY - 5;
    int leftupMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftupMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� ������
    MoveToEx(hdc, leftupMustacheX1, leftupMustacheY1, NULL);
    LineTo(hdc, leftupMustacheX2, leftupMustacheY2);
    MoveToEx(hdc, leftdownMustacheX1, leftdownMustacheY1, NULL);
    LineTo(hdc, leftdownMustacheX2, leftdownMustacheY2);

    // ������ ���� �� �׸���
    int rightupMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightupMustacheY1 = centerY + 40;
    int rightupMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightupMustacheY2 = centerY + 25;

    //  ������ ���� �Ʒ� �׸���
    int rightdownMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightdownMustacheY1 = centerY - 5;
    int rightdownMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightdownMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� ������
    MoveToEx(hdc, rightupMustacheX1, rightupMustacheY1, NULL);
    LineTo(hdc, rightupMustacheX2, rightupMustacheY2);
    MoveToEx(hdc, rightdownMustacheX1, rightdownMustacheY1, NULL);
    LineTo(hdc, rightdownMustacheX2, rightdownMustacheY2);

    // ����� �귯�� ����
    DeleteObject(hSkinBrush);
    DeleteObject(hMouthBrush);
}
void DrawBonobonoCloseEye(HDC hdc) {
    // Bonobono �׸���
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(127, 200, 255)); // �Ǻλ�
    HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 150, 255)); // �Ի�

    // â �߾� ���
    int centerX = 400; // �߾� x ��ǥ
    int centerY = 300; // �߾� y ��ǥ

    // Bonobono �� �׸���
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, centerX - 100, centerY - 100, centerX + 100, centerY + 100);

    // Bonobono ���� �� �׸��� (���� ����)
    int leftEyeX1 = centerX - 80 - leftEyeOffset;
    int leftEyeY1 = centerY + 10 + leftEyeOffset;
    int leftEyeX2 = centerX - 95 - leftEyeOffset;
    int leftEyeY2 = centerY + leftEyeOffset;
    int leftEyeX3 = centerX - 80 - leftEyeOffset;
    int leftEyeY3 = centerY + 10 + leftEyeOffset;
    int leftEyeX4 = centerX - 95 - leftEyeOffset;
    int leftEyeY4 = centerY - 20 - leftEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // ���� ����
    MoveToEx(hdc, leftEyeX1, leftEyeY1, NULL);
    LineTo(hdc, leftEyeX2, leftEyeY2);
    MoveToEx(hdc, leftEyeX3, leftEyeY3, NULL);
    LineTo(hdc, leftEyeX4, leftEyeY4);

    // Bonobono ������ �� �׸��� (���� ����)
    int rightEyeX1 = centerX + 80 + rightEyeOffset;
    int rightEyeY1 = centerY + 10 + rightEyeOffset;
    int rightEyeX2 = centerX + 95 + rightEyeOffset;
    int rightEyeY2 = centerY + rightEyeOffset;
    int rightEyeX3 = centerX + 80 + rightEyeOffset;
    int rightEyeY3 = centerY + 10 + rightEyeOffset;
    int rightEyeX4 = centerX + 95 + rightEyeOffset;
    int rightEyeY4 = centerY - 20 - rightEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // ���� ����
    MoveToEx(hdc, rightEyeX1, rightEyeY1, NULL);
    LineTo(hdc, rightEyeX2, rightEyeY2);
    MoveToEx(hdc, rightEyeX3, rightEyeY3, NULL);
    LineTo(hdc, rightEyeX4, rightEyeY4);

    // Bonobono �� �׸���
    SelectObject(hdc, hMouthBrush);
    Ellipse(hdc, centerX - 11, centerY + 20, centerX + 11, centerY + 60);

    // Bonobono �� �� �׸���
    int noseWidth = 8;
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255))); // �� �ڻ�

    // ���� �� ��
    int leftNoseX = centerX - noseWidth / 2 - leftEyeOffset;
    int leftNoseRadius = 16;
    Ellipse(hdc, leftNoseX - leftNoseRadius - 2, centerY + 20 - leftNoseRadius - 2, leftNoseX + leftNoseRadius + 6, centerY + 20 + leftNoseRadius + 2);

    // ������ �� ��
    int rightNoseX = centerX + noseWidth / 2 + rightEyeOffset;
    int rightNoseRadius = 16;
    Ellipse(hdc, rightNoseX - rightNoseRadius - 6, centerY + 20 - rightNoseRadius - 2, rightNoseX + rightNoseRadius + 2, centerY + 20 + rightNoseRadius + 2);

    // Bonobono ���� �� �׸���
    int noseRadius = 12;
    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� �ڻ�
    Ellipse(hdc, centerX - noseRadius - 4, centerY + 25 - noseRadius - 2 - 20, centerX + noseRadius + 4, centerY + 25 + noseRadius + 2 - 20);

    // ���� ���� �� �׸���
    int leftdownMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftdownMustacheY1 = centerY + 40;
    int leftdownMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftdownMustacheY2 = centerY + 25;

    // ���� ���� �Ʒ� �׸���
    int leftupMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftupMustacheY1 = centerY - 5;
    int leftupMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftupMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� ������
    MoveToEx(hdc, leftupMustacheX1, leftupMustacheY1, NULL);
    LineTo(hdc, leftupMustacheX2, leftupMustacheY2);
    MoveToEx(hdc, leftdownMustacheX1, leftdownMustacheY1, NULL);
    LineTo(hdc, leftdownMustacheX2, leftdownMustacheY2);

    // ������ ���� �� �׸���
    int rightupMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightupMustacheY1 = centerY + 40;
    int rightupMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightupMustacheY2 = centerY + 25;

    // ������ ���� �Ʒ� �׸���
    int rightdownMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightdownMustacheY1 = centerY - 5;
    int rightdownMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightdownMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // ���� ������
    MoveToEx(hdc, rightupMustacheX1, rightupMustacheY1, NULL);
    LineTo(hdc, rightupMustacheX2, rightupMustacheY2);
    MoveToEx(hdc, rightdownMustacheX1, rightdownMustacheY1, NULL);
    LineTo(hdc, rightdownMustacheX2, rightdownMustacheY2);

    // ����� �귯�� ����
    DeleteObject(hSkinBrush);
    DeleteObject(hMouthBrush);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MyWindow"), NULL };
    RegisterClassEx(&wc);

    // Ŀ�� ����
    hCrossCursor = LoadCursor(NULL, IDC_CROSS);

    HWND hWnd = CreateWindow(_T("MyWindow"), _T("������"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);

    // �߰� ��ư ����
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonMargin = 16; // ������ ����

    int left = 8;
    int top = 8;

    hBox = CreateWindow(_T("BUTTON"), _T("Box"), WS_CHILD | WS_VISIBLE, left, top, buttonWidth, buttonHeight, hWnd, NULL, wc.hInstance, NULL);

    left = left + buttonWidth;
    hCircle = CreateWindow(_T("BUTTON"), _T("Circle"), WS_CHILD | WS_VISIBLE, left, top, buttonWidth, buttonHeight, hWnd, NULL, wc.hInstance, NULL);

    left = left + buttonWidth;
    hBonobono = CreateWindow(_T("BUTTON"), _T("Bonobono"), WS_CHILD | WS_VISIBLE, left, top, buttonWidth, buttonHeight, hWnd, NULL, wc.hInstance, NULL);

    left = left + buttonWidth;
    hRyan = CreateWindow(_T("BUTTON"), _T("Ryan"), WS_CHILD | WS_VISIBLE, left, top, buttonWidth, buttonHeight, hWnd, NULL, wc.hInstance, NULL);

    left = left + buttonWidth;
    hCube = CreateWindow(_T("BUTTON"), _T("Cube"), WS_CHILD | WS_VISIBLE, left, top, buttonWidth, buttonHeight, hWnd, NULL, wc.hInstance, NULL);

    // Bonobono�� ������ ������ �귯�� ����
    hBonobonoBrush = CreateSolidBrush(RGB(255, 240, 200));

    // ����� ���� ����
    int boxWidth = 800;
    int boxHeight = 480;  // �� ũ�⸦ 800x480���� ����

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // ����� �귯�� ����
    DeleteObject(hBonobonoBrush);

    UnregisterClass(_T("MyWindow"), wc.hInstance);

    return 0;
}
// Bonobono�� ���¸� ��Ÿ���� ������ �߰�
enum BonobonoState {
    BONO_INITIAL,
    BONO_VISIBLE,
    BONO_EYES_CLOSED,
};

// ���� �߰�
bool isBonobonoButtonPressed = false;
HWND hCurrentButton = NULL;
BonobonoState bonobonoState = BONO_INITIAL;
bool isEyesClosed = false; // ���� ���� �ִ��� ���θ� ��Ÿ���� ����

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SETCURSOR: // ���콺 Ŀ�� ����
        SetCursor(hCrossCursor);
        return TRUE;

        // ��ư Ŭ�� �̺�Ʈ ó��
    case WM_COMMAND:
        if (LOWORD(wParam) == GetDlgCtrlID(hBonobono)) {
            SetFocus(hWnd);
            if (bonobonoState == BONO_INITIAL) {
                HDC hdc = GetDC(hWnd);
                DrawBonobono(hdc);
                ReleaseDC(hWnd, hdc);
                bonobonoState = BONO_VISIBLE;

                // ���� ��Ŀ���� Bonobono ��ư���� ����
                hCurrentButton = hBonobono;
                SetFocus(hWnd);
            }
        }
        return 0;

        // �����̽��� �̺�Ʈ ó��
    case WM_KEYDOWN:
        if (wParam == VK_SPACE && bonobonoState == BONO_VISIBLE) {
            // Bonobono ��ư�� ���� ������ ���� �� ���ų� ���� ������ ����
            HDC hdc = GetDC(hWnd);
            DrawBonobonoCloseEye(hdc);
            ReleaseDC(hWnd, hdc);
            bonobonoState = BONO_EYES_CLOSED;
        }
        return 0;

    case WM_KEYUP:
        if (wParam == VK_SPACE && bonobonoState == BONO_EYES_CLOSED) {
            // Bonobono ��ư�� ���� ������ ���� �� ���ų� ���� ������ ����
            HDC hdc = GetDC(hWnd);
            DrawBonobono(hdc);
            ReleaseDC(hWnd, hdc);
            bonobonoState = BONO_VISIBLE;
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

}
