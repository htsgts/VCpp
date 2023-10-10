#include <windows.h>

// 전역 변수
HWND hwnd; // 그림판 창의 핸들
RECT rect; // 그림판 창의 사각 영역
int x1, y1, x2, y2; // 두 개의 사각형의 좌표
int step = 10; // 이동 스텝
HBRUSH redBrush, blueBrush; // 빨간색과 파란색 브러시
BOOL isHit = FALSE; // 충돌 상태 저장

// 텍스트 출력 함수
void DrawTextOnPaint(HDC hdc) {
    // "Hit" 텍스트 그리기
    if (isHit) {
        TextOut(hdc, 10, 10, L"Hit!", 4); //부딪힌 경우
    }
    else {
        TextOut(hdc, 10, 10, L"Not Hit!", 7); // 아닌 경우
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
    if (isHit) {
        isHit = FALSE; // 충돌 상태 초기화
        // "Hit" 텍스트를 지우기 위해 화면을 다시 그리도록 함
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

    // 충돌 검사
    if (x1 < x2 + 100 && x1 + 50 > x2 && y1 < y2 + 100 && y1 + 50 > y2) {
        isHit = TRUE; // 충돌 상태 설정
    }

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
        x1 = 50;
        y1 = 50;
        x2 = 200;
        y2 = 200;

        // 빨간색과 파란색 브러시 생성
        blueBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색
        redBrush = CreateSolidBrush(RGB(255, 0, 0)); // 빨간색
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

        // 새로운 사각형 그리기
        DrawRect(hdc, x2, y2, redBrush, 100, 100); // 빨간색 사각형

        DrawRect(hdc, x1, y1, blueBrush, 50, 50); // 파란색 사각형

        // 텍스트 출력
        DrawTextOnPaint(hdc);

        EndPaint(hwnd, &ps);
        break;
    case WM_CLOSE:
        // 브러시 해제
        DeleteObject(blueBrush);
        DeleteObject(redBrush);

        // 윈도우 종료 시 종료
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
