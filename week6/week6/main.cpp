#include <windows.h>

// 전역 변수
HWND hwnd; // 그림판 창의 핸들
RECT rect; // 그림판 창의 사각 영역
int pinkBoxX, pinkBoxY; // 핑크 박스의 좌표
int blueBoxX, blueBoxY; // 파란 박스의 좌표
int boxSize = 50; // 박스 크기
int step = 1; // 이동 스텝
BOOL isHit = FALSE; // 충돌 상태 저장
HBRUSH pinkBrush, blueBrush; // 핑크색과 파란색 브러시

// 텍스트 출력 함수
void DrawTextOnPaint(HDC hdc) {
    if (isHit) {
        TextOut(hdc, 10, 10, L"Hit!", 4);
    }
    else {
        TextOut(hdc, 10, 10, L"NotHit!", 7);
    }
}

// 사각형 그리기 함수
void DrawRect(HDC hdc, int x, int y, HBRUSH brush, int width, int height) {
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);
    Rectangle(hdc, x, y, x + width, y + height);
    SelectObject(hdc, oldBrush);
}

// 키보드 입력 처리 함수
void ProcessKeyboardInput(int key) {
    // 키를 누르는 동안 이동할 거리 계산
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

    // 파란 박스의 새로운 위치 계산
    int newBlueBoxX = blueBoxX + deltaX;
    int newBlueBoxY = blueBoxY + deltaY;

    // 충돌 검사
    if (newBlueBoxX < pinkBoxX + boxSize && newBlueBoxX + boxSize > pinkBoxX && newBlueBoxY < pinkBoxY + boxSize && newBlueBoxY + boxSize > pinkBoxY) {
        isHit = TRUE;
    }
    else {
        isHit = FALSE;
        // 밖으로 나갈 때 텍스트를 지우기 위해 화면을 다시 그리도록 함
        InvalidateRect(hwnd, NULL, TRUE);
    }

    // 새로운 위치로 파란 박스 이동
    blueBoxX = newBlueBoxX;
    blueBoxY = newBlueBoxY;

    // 윈도우를 다시 그리기
    InvalidateRect(hwnd, NULL, TRUE);
}

// 윈도우 프로시저
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    HDC hdc;
    PAINTSTRUCT ps;

    switch (msg) {
    case WM_CREATE:
        // 윈도우 생성 시 초기화
        pinkBoxX = 200;
        pinkBoxY = 200;
        blueBoxX = 50;
        blueBoxY = 50;

        // 핑크색과 파란색 브러시 생성
        pinkBrush = CreateSolidBrush(RGB(255, 192, 203)); // 핑크색
        blueBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색
        break;
    case WM_KEYDOWN:
        // 키보드 입력 처리
        ProcessKeyboardInput(wParam);
        break;
    case WM_PAINT:
        // 화면 다시 그리기
        hdc = BeginPaint(hwnd, &ps);

        // 전체 클라이언트 영역을 지우고
        FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

        // 핑크 박스 그리기
        DrawRect(hdc, pinkBoxX, pinkBoxY, pinkBrush, boxSize+50, boxSize+50);

        // 파란 박스 그리기
        DrawRect(hdc, blueBoxX, blueBoxY, blueBrush, boxSize, boxSize);

        // 텍스트 출력
        DrawTextOnPaint(hdc);

        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        // 브러시 해제
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
