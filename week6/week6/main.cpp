#include <windows.h>

// ���� ����
HWND hwnd; // �׸��� â�� �ڵ�
RECT rect; // �׸��� â�� �簢 ����
int pinkBoxX, pinkBoxY; // ��ũ �ڽ��� ��ǥ
int blueBoxX, blueBoxY; // �Ķ� �ڽ��� ��ǥ
int boxSize = 50; // �ڽ� ũ��
int step = 1; // �̵� ����
BOOL isHit = FALSE; // �浹 ���� ����
HBRUSH pinkBrush, blueBrush; // ��ũ���� �Ķ��� �귯��

// �ؽ�Ʈ ��� �Լ�
void DrawTextOnPaint(HDC hdc) {
    if (isHit) {
        TextOut(hdc, 10, 10, L"Hit!", 4);
    }
    else {
        TextOut(hdc, 10, 10, L"NotHit!", 7);
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
    // Ű�� ������ ���� �̵��� �Ÿ� ���
    int deltaX = 0;
    int deltaY = 0;

    switch (key) {
    case VK_LEFT:
        deltaX = -step;
        break;
    case VK_RIGHT:
        deltaX = step;
        break;
    case VK_UP:
        deltaY = -step;
        break;
    case VK_DOWN:
        deltaY = step;
        break;
    }

    // �Ķ� �ڽ��� ���ο� ��ġ ���
    int newBlueBoxX = blueBoxX + deltaX;
    int newBlueBoxY = blueBoxY + deltaY;

    // �浹 �˻�
    if (newBlueBoxX < pinkBoxX + boxSize && newBlueBoxX + boxSize > pinkBoxX && newBlueBoxY < pinkBoxY + boxSize && newBlueBoxY + boxSize > pinkBoxY) {
        isHit = TRUE;
    }
    else {
        isHit = FALSE;
        // ������ ���� �� �ؽ�Ʈ�� ����� ���� ȭ���� �ٽ� �׸����� ��
        InvalidateRect(hwnd, NULL, TRUE);
    }

    // ���ο� ��ġ�� �Ķ� �ڽ� �̵�
    blueBoxX = newBlueBoxX;
    blueBoxY = newBlueBoxY;

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
        pinkBoxX = 200;
        pinkBoxY = 200;
        blueBoxX = 50;
        blueBoxY = 50;

        // ��ũ���� �Ķ��� �귯�� ����
        pinkBrush = CreateSolidBrush(RGB(255, 192, 203)); // ��ũ��
        blueBrush = CreateSolidBrush(RGB(0, 0, 255)); // �Ķ���
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

        // ��ũ �ڽ� �׸���
        DrawRect(hdc, pinkBoxX, pinkBoxY, pinkBrush, boxSize+50, boxSize+50);

        // �Ķ� �ڽ� �׸���
        DrawRect(hdc, blueBoxX, blueBoxY, blueBrush, boxSize, boxSize);

        // �ؽ�Ʈ ���
        DrawTextOnPaint(hdc);

        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        // �귯�� ����
        DeleteObject(pinkBrush);
        DeleteObject(blueBrush);

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
