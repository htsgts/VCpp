#include <windows.h>
#include <cmath>
#include "shapes.h"

HBRUSH hFaceBrush;  // 얼굴을 그리는데 사용할 브러시
HBRUSH hEyeBrush;   // 눈을 그리는데 사용할 브러시
HBRUSH hEarBrush;   // 귀를 그리는데 사용할 브러시
HBRUSH hMouthBrush; // 입을 그리는데 사용할 브러시

static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);

POINT startPoint = { 0 };
POINT endPoint = { 0 };
BOOL isDrawingEnabled = FALSE;
BOOL isRectangleMode = TRUE;
BOOL isCircleMode = FALSE;
BOOL isBonobonoMode = FALSE;
BOOL isRyanMode = FALSE;
BOOL isCubeMode = FALSE;
BOOL CircleScale = FALSE;
BOOL isFirstClick = TRUE;
RECT dragRect;
POINT startPoint1 = { 0 };
POINT endPoint1 = { 0 };
int button = 0;
int isMouseLButtonPressed = 0;
int isMouseRButtonPressed = 0;

void DrawRyan(HDC hdc, int left, int top, int right, int bottom)
{
    // 라이언 그림 그리기

    // 왼쪽 귀 (노란색)
    SelectObject(hdc, hEarBrush);
    HBRUSH hLeftEarColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 귀
    SelectObject(hdc, hLeftEarColor);
    Ellipse(hdc, left + 60, top + 110, left + 130, top + 190);  // 왼쪽 귀의 높이를 높임
    DeleteObject(hLeftEarColor);

    // 오른쪽 귀 (노란색)
    SelectObject(hdc, hEarBrush);
    HBRUSH hRightEarColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 귀
    SelectObject(hdc, hRightEarColor);
    Ellipse(hdc, left + 280, top + 110, left + 350, top + 190);  // 오른쪽 귀의 높이를 높임
    DeleteObject(hRightEarColor);

    // 얼굴 그리기 (노란색)
    HBRUSH hFaceColor = CreateSolidBrush(RGB(255, 200, 15));  // 노란색 얼굴
    SelectObject(hdc, hFaceColor);
    Ellipse(hdc, left + 100, top + 100, left + 300, top + 300);
    DeleteObject(hFaceColor);

    // 눈썹 그리기 (가운데 정렬)
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    MoveToEx(hdc, left + 150, top + 170, NULL);
    LineTo(hdc, left + 165, top + 170);
    MoveToEx(hdc, left + 250, top + 170, NULL);
    LineTo(hdc, left + 265, top + 170);

    // 눈 그리기 (검정색)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Ellipse(hdc, left + 155, top + 200, left + 170, top + 215);  // 왼쪽 눈
    Ellipse(hdc, left + 245, top + 200, left + 260, top + 215);  // 오른쪽 눈

    // 입 그리기 (가운데 정렬, 흰색)
    HBRUSH hMouthColor = CreateSolidBrush(RGB(255, 255, 255));  // 흰색 입
    SelectObject(hdc, hMouthColor);
    int mouthLeft = left + 190;  // 입 왼쪽 부분
    int mouthRight = left + 210;  // 입 오른쪽 부분
    int mouthTop = top + 230;
    int mouthBottom = top + 250;
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    mouthLeft = left + 210;  // 두 번째 원의 왼쪽 부분
    mouthRight = left + 230;  // 두 번째 원의 오른쪽 부분
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    DeleteObject(hMouthColor);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_SETCURSOR:
    {
        POINT pt;
        GetCursorPos(&pt);
        ScreenToClient(hwnd, &pt);

        RECT rc;
        rc.left = 16;
        rc.top = 90;
        rc.right = 800 - 32;
        rc.bottom = 480 - 56;

        if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
        {
            SetCursor(hCrossCursor);
            return TRUE;
        }
        else
        {
            SetCursor(hArrowCursor);
            return TRUE;
        }
    }
    break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 1) // 사각형 버튼이 클릭된 경우
        {
            isRectangleMode = TRUE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 2) // 원 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = TRUE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 3) {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = TRUE; // "보노보노 모드" 버튼 클릭 시 해당 모드를 활성화
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) // Ryan 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = TRUE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 5) // Cube 버튼이 클릭된 경우
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = TRUE;
            isFirstClick = TRUE;
        }

        break;

    case WM_RBUTTONDOWN:
    {
        if (isRectangleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            button = 1;

            // 클라이언트 좌표를 기반으로 어떤 객체를 클릭했는지 확인하는 코드를 추가합니다.
            // 이 예제에서는 현재 하나의 사각형만 처리하도록 가정합니다.

            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            isMouseRButtonPressed = 1;
            if (PtInRect(&dragRect, clientPoint)) {
                isDrawingEnabled = TRUE;
                startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
            }
            startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
        if (isCircleMode)
        {
            // 마우스 오른쪽 버튼 클릭 이벤트 처리
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            CircleScale = 1;
            isDrawingEnabled = TRUE;
            // 클라이언트 좌표를 기반으로 어떤 객체를 클릭했는지 확인하는 코드를 추가합니다.
            // 이 예제에서는 현재 하나의 사각형만 처리하도록 가정합니다.

            // 선택된 사각형을 드래그할 때 필요한 정보를 저장합니다.
            isMouseRButtonPressed = 1;
            startPoint1 = endPoint1 = clientPoint; // 시작 및 끝 포인트를 현재 마우스 위치로 설정합니다.
        }
    }
    break;
    case WM_LBUTTONDOWN:
        if (isFirstClick)
        {
            POINT pt;
            GetCursorPos(&pt);
            ScreenToClient(hwnd, &pt);

            RECT rc;
            rc.left = 16;
            rc.top = 90;
            rc.right = 800 - 32;
            rc.bottom = 480 - 56;
            button = 0;
            if (pt.x > rc.left && pt.x < rc.right && pt.y > rc.top && pt.y < rc.bottom)
            {
                startPoint.x = LOWORD(lParam);
                startPoint.y = HIWORD(lParam);
                isFirstClick = FALSE;
            }
            isMouseLButtonPressed = 1;
        }
        break;

    case WM_LBUTTONUP:
        if (!isFirstClick)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);
            isDrawingEnabled = TRUE;
            isMouseLButtonPressed = 0;
            RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE);
            isFirstClick = TRUE;
        }
        break;
    case WM_RBUTTONUP:
    {
        isMouseRButtonPressed = 0;
        isDrawingEnabled = TRUE;
        CircleScale = 0;
    }
    break;
    case WM_MOUSEMOVE:
    {
        // 마우스 이동 중
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT 메시지를 유발하여 네모를 화면에 그립니다.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isMouseRButtonPressed)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // 현재 마우스 위치와 시작 클릭 위치 사이의 거리를 계산합니다.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // 선택된 사각형을 이동합니다.
            OffsetRect(&dragRect, deltaX, deltaY);
            button = 1;
            startPoint1 = endPoint1; // 현재 마우스 위치를 새로운 시작점으로 설정합니다.

            InvalidateRect(hwnd, NULL, TRUE);
            // 화면 다시 그리기

        }
    }
    case WM_KEYDOWN:
        if (wParam == VK_SPACE && isBonobonoMode) {
            HDC hdc = GetDC(hwnd);
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
            HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//분홍색
            HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//하얀색
            SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
            Ellipse(hdc, 250, 100, 550, 400);// 얼굴
            SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
            Ellipse(hdc, 377, 244, 424, 322);
            SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
            Ellipse(hdc, 353, 245, 400, 292); //왼쪽 입가
            Ellipse(hdc, 400, 245, 447, 292);
            MoveToEx(hdc, 275, 225, NULL);
            LineTo(hdc, 290, 245); //눈
            MoveToEx(hdc, 514, 245, NULL);
            LineTo(hdc, 529, 225);
            MoveToEx(hdc, 290, 245, NULL);
            LineTo(hdc, 275, 265); //눈
            MoveToEx(hdc, 514, 245, NULL);
            LineTo(hdc, 529, 265);
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 383, 234, 417, 272); //코
            MoveToEx(hdc, 340, 285, NULL);
            LineTo(hdc, 368, 272);
            MoveToEx(hdc, 340, 255, NULL);
            LineTo(hdc, 380, 262);
            MoveToEx(hdc, 430, 275, NULL);
            LineTo(hdc, 468, 282); //오른쪽아래 수염
            MoveToEx(hdc, 470, 255, NULL);
            LineTo(hdc, 420, 272);

            ReleaseDC(hwnd, hdc);
        }
        break;

    case WM_KEYUP:
        if (wParam == VK_SPACE) {
            InvalidateRect(hwnd, NULL, TRUE);
        }
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        RECT rc;
        GetClientRect(hwnd, &rc);

        if (isBonobonoMode) {
            // 배경을 그립니다.
            HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // 배경색 지정
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200)); // 배경색 지정
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);
            HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//분홍색
            HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//하얀색
            SelectObject(hdc, hEllipseBrush); // 파랑색 브러시 선택
            Ellipse(hdc, 250, 100, 550, 400);// 얼굴
            SelectObject(hdc, ddllipseBrush); // 파랑색 브러시 선택
            Ellipse(hdc, 377, 244, 424, 322);
            SelectObject(hdc, xxllipseBrush); // 흰색 브러시 선택
            Ellipse(hdc, 353, 245, 400, 292); //왼쪽 입가
            Ellipse(hdc, 400, 245, 447, 292);
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 275, 225, 284, 242); //눈
            Ellipse(hdc, 525, 225, 534, 242);
            SelectObject(hdc, xxllipseBrush);
            Ellipse(hdc, 278, 228, 281, 236); //왼쪽 안눈
            Ellipse(hdc, 528, 227, 531, 236); //오른쪽 안 눈
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 383, 234, 417, 272); //코
            MoveToEx(hdc, 340, 285, NULL);
            LineTo(hdc, 368, 272);
            MoveToEx(hdc, 340, 255, NULL);
            LineTo(hdc, 380, 262);
            MoveToEx(hdc, 430, 275, NULL);
            LineTo(hdc, 468, 282); //오른쪽아래 수염
            MoveToEx(hdc, 470, 255, NULL);
            LineTo(hdc, 420, 272);
        }
        // 그리기를 위한 좌표 계산
        int left1 = 16;
        int top1 = 90;
        int right1 = rc.right - 16;
        int bottom1 = rc.bottom - 16;

        // 패딩과 마진이 8px인 사각형 테두리 그리기
        RECT rect1 = { left1, top1, right1, bottom1 };
        FrameRect(hdc, &rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));

        int left2 = 8;
        int top2 = 8;
        int right2 = rc.right - 8;
        int bottom2 = rc.bottom - 8;

        // 패딩과 마진이 8px인 사각형 테두리 그리기
        RECT rect2 = { left2, top2, right2, bottom2 };
        FrameRect(hdc, &rect2, (HBRUSH)GetStockObject(BLACK_BRUSH));

        if (isRectangleMode && (button == 0))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // 드래그 중인 상자 그리기
            dragRect.left = min(startPoint.x, endPoint.x);
            dragRect.top = min(startPoint.y, endPoint.y);
            dragRect.right = max(startPoint.x, endPoint.x);
            dragRect.bottom = max(startPoint.y, endPoint.y);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &dragRect, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);
        }
        else if (isRectangleMode && (button == 1))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // 핑크 브러시 생성
            FillRect(hdc, &dragRect, hBrush); // 핑크색 상자 그리기
            DeleteObject(hBrush);
        }
        else if (isCircleMode && isDrawingEnabled)
        {
            // 원 그리기
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // 파란색 브러시 생성
            float radius = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2)); // 두 점 사이의 거리를 반지름으로 설정
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius); // 원 그리기
            DeleteObject(hBrush);
        }
        else if (isCircleMode && CircleScale)
        {

        }
        else if (isRyanMode)
        {
            // 라이언 그리기
            int ryanLeft = min(startPoint.x, endPoint.x);   // 라이언의 좌측 X 좌표를 드래그 시작점으로 설정
            int ryanTop = min(startPoint.y, endPoint.y);    // 라이언의 상단 Y 좌표를 드래그 시작점으로 설정
            int ryanRight = min(startPoint.x, endPoint.x);    // 라이언의 우측 X 좌표를 드래그 끝점으로 설정
            int ryanBottom = max(startPoint.y, endPoint.y);   // 라이언의 하단 Y 좌표를 드래그 끝점으로 설정


            DrawRyan(hdc, ryanLeft, ryanTop, ryanRight, ryanBottom);
        }

        ReleaseDC(hwnd, hdc);
        EndPaint(hwnd, &ps);
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

 int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    const wchar_t CLASS_NAME[] = L"Sample Window Class";
    const wchar_t WINDOW_NAME[] = L"Sample Window";

    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = CreateSolidBrush(RGB(255, 240, 200)); // Background color as (255, 240, 200)
    wc.hCursor = LoadCursor(NULL, IDC_CROSS);
    LPCTSTR cursor = IDC_HAND;

    RegisterClass(&wc);

    HWND hwnd = CreateWindowEx(
        0,                          // Optional window styles.
        CLASS_NAME,                 // Window class
        WINDOW_NAME,                // Window text
        WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, // Window style without sizing options

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, 810, 480,

        NULL,       // Parent window   
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

    if (hwnd == NULL) {
        return 0;
    }
    int buttonWidth = 140;
    int buttonHeight = 64;
    int buttonSpacing = 12;
    int leftMargin = 24;

    // Create a box with 8-pixel margin and padding
    CreateWindow(TEXT("BUTTON"), TEXT("Box"), WS_VISIBLE | WS_CHILD, leftMargin - 8, 16, buttonWidth, buttonHeight, hwnd, (HMENU)1, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Circle"), WS_VISIBLE | WS_CHILD, leftMargin - 4 + buttonWidth + buttonSpacing + 1, 16, buttonWidth, buttonHeight, hwnd, (HMENU)2, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Bonobono"), WS_VISIBLE | WS_CHILD, leftMargin + 2 * (buttonWidth + buttonSpacing) + 2, 16, buttonWidth, buttonHeight, hwnd, (HMENU)3, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Ryan"), WS_VISIBLE | WS_CHILD, leftMargin + 3 * (buttonWidth + buttonSpacing) + 3, 16, buttonWidth, buttonHeight, hwnd, (HMENU)4, NULL, NULL);
    CreateWindow(TEXT("BUTTON"), TEXT("Cube"), WS_VISIBLE | WS_CHILD, leftMargin + 4 * (buttonWidth + buttonSpacing) + 4, 16, buttonWidth, buttonHeight, hwnd, (HMENU)5, NULL, NULL);
    ShowWindow(hwnd, nCmdShow);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}