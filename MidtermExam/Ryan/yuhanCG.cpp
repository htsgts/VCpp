#include <tchar.h>
#include <Windows.h>
#include "yuhanCG.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hBox, hCircle, hBonobono, hRyan, hCube;  // 상자와 5개의 버튼 핸들
HCURSOR hCrossCursor; // CROSS 커서 핸들

HBRUSH hBonobonoBrush; // Bonobono의 색상을 저장할 브러시 핸들

// Bonobono의 눈 위치를 나타내는 변수
int leftEyeOffset = -20; // 왼쪽 눈을 20픽셀 아래로 내립니다.
int rightEyeOffset = -20; // 오른쪽 눈을 20픽셀 아래로 내립니다.

// Bonobono의 눈 색상 교환 변수
COLORREF eyeBlackColor = RGB(0, 0, 0);
COLORREF eyeWhiteColor = RGB(255, 255, 255);

void DrawBonobono(HDC hdc) {
    // Bonobono 그리기
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(127, 200, 255)); // 피부색
    HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입색

    // 창 중앙 계산
    int centerX = 400; // 중앙 x 좌표
    int centerY = 300; // 중앙 y 좌표

    // Bonobono 얼굴 그리기
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, centerX - 100, centerY - 100, centerX + 100, centerY + 100);

    // Bonobono 왼쪽 눈 그리기
    int leftEyeX = centerX - 95 - leftEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // 검은 눈색
    Ellipse(hdc, leftEyeX - 4, centerY - 20, leftEyeX + 4, centerY - 6);
    SelectObject(hdc, CreateSolidBrush(eyeWhiteColor)); // 흰 눈색
    Ellipse(hdc, leftEyeX - 2, centerY - 16, leftEyeX + 2, centerY - 10);

    // Bonobono 오른쪽 눈 그리기
    int rightEyeX = centerX + 95 + rightEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // 검은 눈색
    Ellipse(hdc, rightEyeX - 4, centerY - 20, rightEyeX + 4, centerY - 6);
    SelectObject(hdc, CreateSolidBrush(eyeWhiteColor)); // 흰 눈색
    Ellipse(hdc, rightEyeX - 2, centerY - 16, rightEyeX + 2, centerY - 10);

    // Bonobono 입 그리기
    SelectObject(hdc, hMouthBrush);
    Ellipse(hdc, centerX - 11, centerY + 20, centerX + 11, centerY + 60);

    // Bonobono 흰 코 그리기
    int noseWidth = 8;
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255))); // 흰 코색

    // 왼쪽 흰 코
    int leftNoseX = centerX - noseWidth / 2 - leftEyeOffset;
    int leftNoseRadius = 16;
    Ellipse(hdc, leftNoseX - leftNoseRadius - 2, centerY + 20 - leftNoseRadius - 2, leftNoseX + leftNoseRadius + 6, centerY + 20 + leftNoseRadius + 2);

    // 오른쪽 흰 코
    int rightNoseX = centerX + noseWidth / 2 + rightEyeOffset;
    int rightNoseRadius = 16;
    Ellipse(hdc, rightNoseX - rightNoseRadius - 6, centerY + 20 - rightNoseRadius - 2, rightNoseX + rightNoseRadius + 2, centerY + 20 + rightNoseRadius + 2);

    // Bonobono 검은 코 그리기 
    int noseRadius = 12;
    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 코색
    Ellipse(hdc, centerX - noseRadius - 4, centerY + 25 - noseRadius - 2 - 20, centerX + noseRadius + 4, centerY + 25 + noseRadius + 2 - 20);

    // 왼쪽 수염 위 그리기
    int leftdownMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftdownMustacheY1 = centerY + 40;
    int leftdownMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftdownMustacheY2 = centerY + 25;

    // 왼쪽 수염 아래 그리기
    int leftupMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftupMustacheY1 = centerY - 5;
    int leftupMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftupMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 수염색
    MoveToEx(hdc, leftupMustacheX1, leftupMustacheY1, NULL);
    LineTo(hdc, leftupMustacheX2, leftupMustacheY2);
    MoveToEx(hdc, leftdownMustacheX1, leftdownMustacheY1, NULL);
    LineTo(hdc, leftdownMustacheX2, leftdownMustacheY2);

    // 오른쪽 수염 위 그리기
    int rightupMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightupMustacheY1 = centerY + 40;
    int rightupMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightupMustacheY2 = centerY + 25;

    //  오른쪽 수염 아래 그리기
    int rightdownMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightdownMustacheY1 = centerY - 5;
    int rightdownMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightdownMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 수염색
    MoveToEx(hdc, rightupMustacheX1, rightupMustacheY1, NULL);
    LineTo(hdc, rightupMustacheX2, rightupMustacheY2);
    MoveToEx(hdc, rightdownMustacheX1, rightdownMustacheY1, NULL);
    LineTo(hdc, rightdownMustacheX2, rightdownMustacheY2);

    // 사용한 브러시 해제
    DeleteObject(hSkinBrush);
    DeleteObject(hMouthBrush);
}
void DrawBonobonoCloseEye(HDC hdc) {
    // Bonobono 그리기
    HBRUSH hSkinBrush = CreateSolidBrush(RGB(127, 200, 255)); // 피부색
    HBRUSH hMouthBrush = CreateSolidBrush(RGB(255, 150, 255)); // 입색

    // 창 중앙 계산
    int centerX = 400; // 중앙 x 좌표
    int centerY = 300; // 중앙 y 좌표

    // Bonobono 얼굴 그리기
    SelectObject(hdc, hSkinBrush);
    Ellipse(hdc, centerX - 100, centerY - 100, centerX + 100, centerY + 100);

    // Bonobono 왼쪽 눈 그리기 (눈을 감음)
    int leftEyeX1 = centerX - 80 - leftEyeOffset;
    int leftEyeY1 = centerY + 10 + leftEyeOffset;
    int leftEyeX2 = centerX - 95 - leftEyeOffset;
    int leftEyeY2 = centerY + leftEyeOffset;
    int leftEyeX3 = centerX - 80 - leftEyeOffset;
    int leftEyeY3 = centerY + 10 + leftEyeOffset;
    int leftEyeX4 = centerX - 95 - leftEyeOffset;
    int leftEyeY4 = centerY - 20 - leftEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // 검은 눈색
    MoveToEx(hdc, leftEyeX1, leftEyeY1, NULL);
    LineTo(hdc, leftEyeX2, leftEyeY2);
    MoveToEx(hdc, leftEyeX3, leftEyeY3, NULL);
    LineTo(hdc, leftEyeX4, leftEyeY4);

    // Bonobono 오른쪽 눈 그리기 (눈을 감음)
    int rightEyeX1 = centerX + 80 + rightEyeOffset;
    int rightEyeY1 = centerY + 10 + rightEyeOffset;
    int rightEyeX2 = centerX + 95 + rightEyeOffset;
    int rightEyeY2 = centerY + rightEyeOffset;
    int rightEyeX3 = centerX + 80 + rightEyeOffset;
    int rightEyeY3 = centerY + 10 + rightEyeOffset;
    int rightEyeX4 = centerX + 95 + rightEyeOffset;
    int rightEyeY4 = centerY - 20 - rightEyeOffset;
    SelectObject(hdc, CreateSolidBrush(eyeBlackColor)); // 검은 눈색
    MoveToEx(hdc, rightEyeX1, rightEyeY1, NULL);
    LineTo(hdc, rightEyeX2, rightEyeY2);
    MoveToEx(hdc, rightEyeX3, rightEyeY3, NULL);
    LineTo(hdc, rightEyeX4, rightEyeY4);

    // Bonobono 입 그리기
    SelectObject(hdc, hMouthBrush);
    Ellipse(hdc, centerX - 11, centerY + 20, centerX + 11, centerY + 60);

    // Bonobono 흰 코 그리기
    int noseWidth = 8;
    SelectObject(hdc, CreateSolidBrush(RGB(255, 255, 255))); // 흰 코색

    // 왼쪽 흰 코
    int leftNoseX = centerX - noseWidth / 2 - leftEyeOffset;
    int leftNoseRadius = 16;
    Ellipse(hdc, leftNoseX - leftNoseRadius - 2, centerY + 20 - leftNoseRadius - 2, leftNoseX + leftNoseRadius + 6, centerY + 20 + leftNoseRadius + 2);

    // 오른쪽 흰 코
    int rightNoseX = centerX + noseWidth / 2 + rightEyeOffset;
    int rightNoseRadius = 16;
    Ellipse(hdc, rightNoseX - rightNoseRadius - 6, centerY + 20 - rightNoseRadius - 2, rightNoseX + rightNoseRadius + 2, centerY + 20 + rightNoseRadius + 2);

    // Bonobono 검은 코 그리기
    int noseRadius = 12;
    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 코색
    Ellipse(hdc, centerX - noseRadius - 4, centerY + 25 - noseRadius - 2 - 20, centerX + noseRadius + 4, centerY + 25 + noseRadius + 2 - 20);

    // 왼쪽 수염 위 그리기
    int leftdownMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftdownMustacheY1 = centerY + 40;
    int leftdownMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftdownMustacheY2 = centerY + 25;

    // 왼쪽 수염 아래 그리기
    int leftupMustacheX1 = centerX - 50 - leftEyeOffset;
    int leftupMustacheY1 = centerY - 5;
    int leftupMustacheX2 = centerX - 35 - leftEyeOffset;
    int leftupMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 수염색
    MoveToEx(hdc, leftupMustacheX1, leftupMustacheY1, NULL);
    LineTo(hdc, leftupMustacheX2, leftupMustacheY2);
    MoveToEx(hdc, leftdownMustacheX1, leftdownMustacheY1, NULL);
    LineTo(hdc, leftdownMustacheX2, leftdownMustacheY2);

    // 오른쪽 수염 위 그리기
    int rightupMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightupMustacheY1 = centerY + 40;
    int rightupMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightupMustacheY2 = centerY + 25;

    // 오른쪽 수염 아래 그리기
    int rightdownMustacheX1 = centerX + 50 + rightEyeOffset;
    int rightdownMustacheY1 = centerY - 5;
    int rightdownMustacheX2 = centerX + 35 + rightEyeOffset;
    int rightdownMustacheY2 = centerY + 15;

    SelectObject(hdc, CreateSolidBrush(RGB(0, 0, 0))); // 검은 수염색
    MoveToEx(hdc, rightupMustacheX1, rightupMustacheY1, NULL);
    LineTo(hdc, rightupMustacheX2, rightupMustacheY2);
    MoveToEx(hdc, rightdownMustacheX1, rightdownMustacheY1, NULL);
    LineTo(hdc, rightdownMustacheX2, rightdownMustacheY2);

    // 사용한 브러시 해제
    DeleteObject(hSkinBrush);
    DeleteObject(hMouthBrush);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, _T("MyWindow"), NULL };
    RegisterClassEx(&wc);

    // 커서 생성
    hCrossCursor = LoadCursor(NULL, IDC_CROSS);

    HWND hWnd = CreateWindow(_T("MyWindow"), _T("곰돌이"), WS_OVERLAPPEDWINDOW, 100, 100, 800, 600, NULL, NULL, wc.hInstance, NULL);

    HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200));
    SetClassLongPtr(hWnd, GCLP_HBRBACKGROUND, (LONG_PTR)hBrush);

    // 추가 버튼 생성
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonMargin = 16; // 간격을 없앰

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

    // Bonobono의 색상을 저장할 브러시 생성
    hBonobonoBrush = CreateSolidBrush(RGB(255, 240, 200));

    // 드로잉 영역 생성
    int boxWidth = 800;
    int boxHeight = 480;  // 뷰 크기를 800x480으로 설정

    ShowWindow(hWnd, SW_SHOWNORMAL);
    UpdateWindow(hWnd);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 사용한 브러시 해제
    DeleteObject(hBonobonoBrush);

    UnregisterClass(_T("MyWindow"), wc.hInstance);

    return 0;
}
// Bonobono의 상태를 나타내는 열거형 추가
enum BonobonoState {
    BONO_INITIAL,
    BONO_VISIBLE,
    BONO_EYES_CLOSED,
};

// 변수 추가
bool isBonobonoButtonPressed = false;
HWND hCurrentButton = NULL;
BonobonoState bonobonoState = BONO_INITIAL;
bool isEyesClosed = false; // 눈이 감겨 있는지 여부를 나타내는 변수

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_SETCURSOR: // 마우스 커서 설정
        SetCursor(hCrossCursor);
        return TRUE;

        // 버튼 클릭 이벤트 처리
    case WM_COMMAND:
        if (LOWORD(wParam) == GetDlgCtrlID(hBonobono)) {
            SetFocus(hWnd);
            if (bonobonoState == BONO_INITIAL) {
                HDC hdc = GetDC(hWnd);
                DrawBonobono(hdc);
                ReleaseDC(hWnd, hdc);
                bonobonoState = BONO_VISIBLE;

                // 현재 포커스를 Bonobono 버튼으로 설정
                hCurrentButton = hBonobono;
                SetFocus(hWnd);
            }
        }
        return 0;

        // 스페이스바 이벤트 처리
    case WM_KEYDOWN:
        if (wParam == VK_SPACE && bonobonoState == BONO_VISIBLE) {
            // Bonobono 버튼이 눌린 상태일 때만 눈 감거나 여는 동작을 수행
            HDC hdc = GetDC(hWnd);
            DrawBonobonoCloseEye(hdc);
            ReleaseDC(hWnd, hdc);
            bonobonoState = BONO_EYES_CLOSED;
        }
        return 0;

    case WM_KEYUP:
        if (wParam == VK_SPACE && bonobonoState == BONO_EYES_CLOSED) {
            // Bonobono 버튼이 눌린 상태일 때만 눈 감거나 여는 동작을 수행
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
