#include <windows.h>

// ���� ����
HWND hwnd; // �׸��� â�� �ڵ�
RECT rect; // �׸��� â�� �簢 ����
int x1, y1, x2, y2; // �� ���� �簢���� ��ǥ
int step = 10; // �̵� ����
HBRUSH redBrush, blueBrush; // �������� �Ķ��� �귯��
BOOL isHit = FALSE; // �浹 ���� ����

// �ؽ�Ʈ ��� �Լ�
void DrawTextOnPaint(HDC hdc) {
    // "Hit" �ؽ�Ʈ �׸���
    if (isHit) {
        TextOut(hdc, 10, 10, L"Hit!", 4); //�ε��� ���
    }
    else {
        TextOut(hdc, 10, 10, L"Not Hit!", 7); // �ƴ� ���
    }
}

// �簢�� �׸��� �Լ�
void DrawRect(HDC hdc, int x, int y, HBRUSH brush, int width, int height) {
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
}

// Ű���� �Է� ó�� �Լ�
void ProcessKeyboardInput(int key) {
    if (isHit) {
        isHit = FALSE; // �浹 ���� �ʱ�ȭ
        // "Hit" �ؽ�Ʈ�� ����� ���� ȭ���� �ٽ� �׸����� ��
        InvalidateRect(hwnd, NULL, TRUE);
    }

    switch (key) {
    case VK_LEFT:
        x1 -= step;
        break;
    case VK_RIGHT:
        x1 += step;
        break;
    case VK_UP:
        y1 -= step;
        break;
    case VK_DOWN:
        y1 += step;
        break;
    }

    // �浹 �˻�
    if (x1 < x2 + 100 && x1 + 50 > x2 && y1 < y2 + 100 && y1 + 50 > y2) {
        isHit = TRUE; // �浹 ���� ����
    }

    // �����츦 �ٽ� �׸���
    InvalidateRect(hwnd, NULL, TRUE);
}

// ������ ���ν���
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_CREATE:
        // ������ ���� �� �ʱ�ȭ
        x1 = 50;
        y1 = 50;
        x2 = 200;
        y2 = 200;

        // �������� �Ķ��� �귯�� ����
        blueBrush = CreateSolidBrush(RGB(0, 0, 255)); // �Ķ���
        redBrush = CreateSolidBrush(RGB(255, 0, 0)); // ������
        break;
    case WM_KEYDOWN:
        // Ű���� �Է� ó��
        ProcessKeyboardInput(wParam);
        break;
    case WM_PAINT:
        // ȭ�� �ٽ� �׸���
        hdc = BeginPaint(hwnd, &ps);

        // ��ü Ŭ���̾�Ʈ ������ �����
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // ���ο� �簢�� �׸���
        DrawRect(hdc, x2, y2, redBrush, 100, 100); // ������ �簢��

        DrawRect(hdc, x1, y1, blueBrush, 50, 50); // �Ķ��� �簢��

        // �ؽ�Ʈ ���
        DrawTextOnPaint(hdc);

        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        // �귯�� ����
        DeleteObject(blueBrush);
        DeleteObject(redBrush);

        // ������ ���� �� ����
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, L"WinAPI Example", NULL };
    RegisterClassEx(&wc);
    hwnd = CreateWindow(wc.lpszClassName, L"WinAPI Example", WS_OVERLAPPEDWINDOW, 100, 100, 400, 400, NULL, NULL, wc.hInstance, NULL);

    GetClientRect(hwnd, &rect);
    ShowWindow(hwnd, SW_SHOWDEFAULT);
    UpdateWindow(hwnd);

    MSG msg;
    ZeroMemory(&msg, sizeof(msg));
    while (msg.message != WM_QUIT) {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    UnregisterClass(wc.lpszClassName, wc.hInstance);
    return 0;
}
