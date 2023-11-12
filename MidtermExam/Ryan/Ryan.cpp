#include <Windows.h>
#include <tchar.h>


HWND hRyanButton; // 라이언 버튼 핸들

void DrawRyan(HDC hdc, int x, int y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void DrawRyan(HDC hdc, int x, int y);
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    static POINT dragStart; // 드래그 시작 지점 저장
    static bool isDragging = false;

    switch (msg) {
    case WM_COMMAND:
        if (LOWORD(wParam) == GetDlgCtrlID(hRyanButton)) {
            // 라이언 버튼이 눌렸을 때의 동작
            // 여기에서 라이언의 얼굴을 그리는 함수 호출
            HDC hdc = GetDC(hWnd);
            DrawRyan(hdc, 100, 100); // 예시로 위치 (100, 100)에 그림
            ReleaseDC(hWnd, hdc);
        }
        return 0;

    case WM_LBUTTONDOWN:
        if (wParam == MK_LBUTTON) {
            // 왼쪽 마우스 버튼이 눌렸을 때 드래그 시작
            dragStart.x = LOWORD(lParam);
            dragStart.y = HIWORD(lParam);
            isDragging = true;
        }
        return 0;

    case WM_LBUTTONUP:
        if (isDragging) {
            // 왼쪽 마우스 버튼이 떼어졌을 때 드래그 종료
            isDragging = false;
        }
        return 0;

    case WM_MOUSEMOVE:
        if (isDragging) {
            // 마우스 이동 중에는 라이언 이미지를 그림
            HDC hdc = GetDC(hWnd);
            int offsetX = LOWORD(lParam) - dragStart.x;
            int offsetY = HIWORD(lParam) - dragStart.y;
            DrawRyan(hdc, 100 + offsetX, 100 + offsetY); // 예시로 위치 (100, 100)에 그림
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