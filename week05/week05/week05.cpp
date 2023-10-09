#include <windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// 프로그램 진입점인 WinMain 함수입니다.
// hInstance: 현재 실행 중인 프로그램의 인스턴스 핸들
// hPrevInstance: 사용되지 않습니다. (이전 인스턴스 핸들)
// lpCmdLine: 명령행 매개변수
// nCmdShow: 윈도우를 보이게 할 방식을 지정하는 플래그
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    // 윈도우 클래스 등록
    // 윈도우 클래스를 정의하고 등록하여 윈도우를 생성할 준비를 합니다.
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, TEXT("DrawingApp"), NULL };
    RegisterClassEx(&wc);

    // 윈도우 생성
    // 실제 윈도우를 생성하고 윈도우 핸들을 반환합니다.
    HWND hwnd = CreateWindow(TEXT("DrawingApp"), TEXT("그림판"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 800, 600, NULL, NULL, hInstance, NULL);
    if (hwnd == NULL)
    {
        MessageBox(NULL, TEXT("윈도우를 생성할 수 없습니다."), TEXT("에러"), MB_ICONERROR);
        return 1;
    }

    // 윈도우를 화면에 표시합니다.
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // 메시지 루프
    MSG msg;
    BOOL bRet;

    int startX = 0, startY = 0; // 사각형 그리기 시작점
    int endX = 0, endY = 0;   // 사각형 그리기 끝점
    BOOL isDrawing = FALSE;   // 사각형 그리기 상태 여부
    BOOL isMoving = FALSE;    // 사각형 이동 상태 여부
    int offsetX = 0, offsetY = 0; // 이동 거리

    while ((bRet = GetMessage(&msg, NULL, 0, 0)) != 0)
    {
        if (bRet == -1)
        {
            // 에러 발생
            MessageBox(NULL, TEXT("메시지를 가져오는 동안 오류가 발생했습니다."), TEXT("에러"), MB_ICONERROR);
            break;
        }
        else
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        switch (msg.message)
        {
        case WM_LBUTTONDOWN:
            startX = LOWORD(msg.lParam);
            startY = HIWORD(msg.lParam);
            endX = startX;
            endY = startY;
            isDrawing = TRUE;
            break;

        case WM_MOUSEMOVE:
            if (isDrawing)
            {
                endX = LOWORD(msg.lParam);
                endY = HIWORD(msg.lParam);
            }
            else if (isMoving)
            {
                startX = LOWORD(msg.lParam) + offsetX;
                startY = HIWORD(msg.lParam) + offsetY;
                endX = startX + (endX - startX);
                endY = startY + (endY - startY);

                // 화면 다시 그리기
                InvalidateRect(hwnd, NULL, TRUE);
            }
            break;

        case WM_LBUTTONUP:
            if (isDrawing)
            {
                endX = LOWORD(msg.lParam);
                endY = HIWORD(msg.lParam);
                isDrawing = FALSE;

                // 빨간색 사각형 그리기
                HDC hdc = GetDC(hwnd);
                HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
                HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
                Rectangle(hdc, startX, startY, endX, endY);
                SelectObject(hdc, oldBrush);
                DeleteObject(redBrush);
                ReleaseDC(hwnd, hdc);
            }
            break;

        case WM_RBUTTONDOWN:
            if (startX <= LOWORD(msg.lParam) && LOWORD(msg.lParam) <= endX &&
                startY <= HIWORD(msg.lParam) && HIWORD(msg.lParam) <= endY)
            {
                isMoving = TRUE;
                offsetX = startX - LOWORD(msg.lParam);
                offsetY = startY - HIWORD(msg.lParam);
            }
            break;

        case WM_RBUTTONUP:
            isMoving = FALSE;
            break;

        case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // 빨간색 사각형 그리기
            HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
            HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, redBrush);
            Rectangle(hdc, startX, startY, endX, endY);
            SelectObject(hdc, oldBrush);
            DeleteObject(redBrush);

            EndPaint(hwnd, &ps);
            break;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, msg.message, msg.wParam, msg.lParam);
        }
    }

    return (int)msg.wParam;
}
