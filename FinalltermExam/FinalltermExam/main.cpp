#include <windows.h>
#include <cmath>
#include "shapes.h"

HBRUSH hFaceBrush;  // ���� �׸��µ� ����� �귯��
HBRUSH hEyeBrush;   // ���� �׸��µ� ����� �귯��
HBRUSH hEarBrush;   // �͸� �׸��µ� ����� �귯��
HBRUSH hMouthBrush; // ���� �׸��µ� ����� �귯��

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
    // ���̾� �׸� �׸���

    // ���� �� (�����)
    SelectObject(hdc, hEarBrush);
    HBRUSH hLeftEarColor = CreateSolidBrush(RGB(255, 200, 15));  // ����� ��
    SelectObject(hdc, hLeftEarColor);
    Ellipse(hdc, left + 60, top + 110, left + 130, top + 190);  // ���� ���� ���̸� ����
    DeleteObject(hLeftEarColor);

    // ������ �� (�����)
    SelectObject(hdc, hEarBrush);
    HBRUSH hRightEarColor = CreateSolidBrush(RGB(255, 200, 15));  // ����� ��
    SelectObject(hdc, hRightEarColor);
    Ellipse(hdc, left + 280, top + 110, left + 350, top + 190);  // ������ ���� ���̸� ����
    DeleteObject(hRightEarColor);

    // �� �׸��� (�����)
    HBRUSH hFaceColor = CreateSolidBrush(RGB(255, 200, 15));  // ����� ��
    SelectObject(hdc, hFaceColor);
    Ellipse(hdc, left + 100, top + 100, left + 300, top + 300);
    DeleteObject(hFaceColor);

    // ���� �׸��� (��� ����)
    SelectObject(hdc, GetStockObject(BLACK_PEN));
    MoveToEx(hdc, left + 150, top + 170, NULL);
    LineTo(hdc, left + 165, top + 170);
    MoveToEx(hdc, left + 250, top + 170, NULL);
    LineTo(hdc, left + 265, top + 170);

    // �� �׸��� (������)
    SelectObject(hdc, GetStockObject(BLACK_BRUSH));
    Ellipse(hdc, left + 155, top + 200, left + 170, top + 215);  // ���� ��
    Ellipse(hdc, left + 245, top + 200, left + 260, top + 215);  // ������ ��

    // �� �׸��� (��� ����, ���)
    HBRUSH hMouthColor = CreateSolidBrush(RGB(255, 255, 255));  // ��� ��
    SelectObject(hdc, hMouthColor);
    int mouthLeft = left + 190;  // �� ���� �κ�
    int mouthRight = left + 210;  // �� ������ �κ�
    int mouthTop = top + 230;
    int mouthBottom = top + 250;
    Ellipse(hdc, mouthLeft, mouthTop, mouthRight, mouthBottom);

    mouthLeft = left + 210;  // �� ��° ���� ���� �κ�
    mouthRight = left + 230;  // �� ��° ���� ������ �κ�
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
        if (LOWORD(wParam) == 1) // �簢�� ��ư�� Ŭ���� ���
        {
            isRectangleMode = TRUE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 2) // �� ��ư�� Ŭ���� ���
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
            isBonobonoMode = TRUE; // "���뺸�� ���" ��ư Ŭ�� �� �ش� ��带 Ȱ��ȭ
            isRyanMode = FALSE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
            SetFocus(hwnd);
            InvalidateRect(hwnd, NULL, TRUE);
        }
        else if (LOWORD(wParam) == 4) // Ryan ��ư�� Ŭ���� ���
        {
            isRectangleMode = FALSE;
            isCircleMode = FALSE;
            isBonobonoMode = FALSE;
            isRyanMode = TRUE;
            isCubeMode = FALSE;
            isFirstClick = TRUE;
        }
        else if (LOWORD(wParam) == 5) // Cube ��ư�� Ŭ���� ���
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
            // ���콺 ������ ��ư Ŭ�� �̺�Ʈ ó��
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            button = 1;

            // Ŭ���̾�Ʈ ��ǥ�� ������� � ��ü�� Ŭ���ߴ��� Ȯ���ϴ� �ڵ带 �߰��մϴ�.
            // �� ���������� ���� �ϳ��� �簢���� ó���ϵ��� �����մϴ�.

            // ���õ� �簢���� �巡���� �� �ʿ��� ������ �����մϴ�.
            isMouseRButtonPressed = 1;
            if (PtInRect(&dragRect, clientPoint)) {
                isDrawingEnabled = TRUE;
                startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
            }
            startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
        }
        if (isCircleMode)
        {
            // ���콺 ������ ��ư Ŭ�� �̺�Ʈ ó��
            POINTS pt = MAKEPOINTS(lParam);
            POINT clientPoint = { pt.x, pt.y };
            ScreenToClient(hwnd, &clientPoint);
            CircleScale = 1;
            isDrawingEnabled = TRUE;
            // Ŭ���̾�Ʈ ��ǥ�� ������� � ��ü�� Ŭ���ߴ��� Ȯ���ϴ� �ڵ带 �߰��մϴ�.
            // �� ���������� ���� �ϳ��� �簢���� ó���ϵ��� �����մϴ�.

            // ���õ� �簢���� �巡���� �� �ʿ��� ������ �����մϴ�.
            isMouseRButtonPressed = 1;
            startPoint1 = endPoint1 = clientPoint; // ���� �� �� ����Ʈ�� ���� ���콺 ��ġ�� �����մϴ�.
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
        // ���콺 �̵� ��
        if (isMouseLButtonPressed)
        {
            endPoint.x = LOWORD(lParam);
            endPoint.y = HIWORD(lParam);

            // WM_PAINT �޽����� �����Ͽ� �׸� ȭ�鿡 �׸��ϴ�.
            InvalidateRect(hwnd, NULL, TRUE);
        }
        if (isMouseRButtonPressed)
        {
            endPoint1.x = LOWORD(lParam);
            endPoint1.y = HIWORD(lParam);

            // ���� ���콺 ��ġ�� ���� Ŭ�� ��ġ ������ �Ÿ��� ����մϴ�.
            int deltaX = endPoint1.x - startPoint1.x;
            int deltaY = endPoint1.y - startPoint1.y;

            // ���õ� �簢���� �̵��մϴ�.
            OffsetRect(&dragRect, deltaX, deltaY);
            button = 1;
            startPoint1 = endPoint1; // ���� ���콺 ��ġ�� ���ο� ���������� �����մϴ�.

            InvalidateRect(hwnd, NULL, TRUE);
            // ȭ�� �ٽ� �׸���

        }
    }
    case WM_KEYDOWN:
        if (wParam == VK_SPACE && isBonobonoMode) {
            HDC hdc = GetDC(hwnd);
            RECT rect;
            GetClientRect(hwnd, &rect);
            HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // ���� ����
            HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//��ȫ��
            HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//�Ͼ��
            SelectObject(hdc, hEllipseBrush); // �Ķ��� �귯�� ����
            Ellipse(hdc, 250, 100, 550, 400);// ��
            SelectObject(hdc, ddllipseBrush); // �Ķ��� �귯�� ����
            Ellipse(hdc, 377, 244, 424, 322);
            SelectObject(hdc, xxllipseBrush); // ��� �귯�� ����
            Ellipse(hdc, 353, 245, 400, 292); //���� �԰�
            Ellipse(hdc, 400, 245, 447, 292);
            MoveToEx(hdc, 275, 225, NULL);
            LineTo(hdc, 290, 245); //��
            MoveToEx(hdc, 514, 245, NULL);
            LineTo(hdc, 529, 225);
            MoveToEx(hdc, 290, 245, NULL);
            LineTo(hdc, 275, 265); //��
            MoveToEx(hdc, 514, 245, NULL);
            LineTo(hdc, 529, 265);
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 383, 234, 417, 272); //��
            MoveToEx(hdc, 340, 285, NULL);
            LineTo(hdc, 368, 272);
            MoveToEx(hdc, 340, 255, NULL);
            LineTo(hdc, 380, 262);
            MoveToEx(hdc, 430, 275, NULL);
            LineTo(hdc, 468, 282); //�����ʾƷ� ����
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
            // ����� �׸��ϴ�.
            HBRUSH bBrush = CreateSolidBrush(RGB(0, 0, 0)); // ���� ����
            HBRUSH hBrush = CreateSolidBrush(RGB(255, 240, 200)); // ���� ����
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);
            HBRUSH hEllipseBrush = CreateSolidBrush(RGB(127, 200, 255));
            HBRUSH ddllipseBrush = CreateSolidBrush(RGB(255, 150, 255));//��ȫ��
            HBRUSH xxllipseBrush = CreateSolidBrush(RGB(255, 255, 255));//�Ͼ��
            SelectObject(hdc, hEllipseBrush); // �Ķ��� �귯�� ����
            Ellipse(hdc, 250, 100, 550, 400);// ��
            SelectObject(hdc, ddllipseBrush); // �Ķ��� �귯�� ����
            Ellipse(hdc, 377, 244, 424, 322);
            SelectObject(hdc, xxllipseBrush); // ��� �귯�� ����
            Ellipse(hdc, 353, 245, 400, 292); //���� �԰�
            Ellipse(hdc, 400, 245, 447, 292);
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 275, 225, 284, 242); //��
            Ellipse(hdc, 525, 225, 534, 242);
            SelectObject(hdc, xxllipseBrush);
            Ellipse(hdc, 278, 228, 281, 236); //���� �ȴ�
            Ellipse(hdc, 528, 227, 531, 236); //������ �� ��
            SelectObject(hdc, bBrush);
            Ellipse(hdc, 383, 234, 417, 272); //��
            MoveToEx(hdc, 340, 285, NULL);
            LineTo(hdc, 368, 272);
            MoveToEx(hdc, 340, 255, NULL);
            LineTo(hdc, 380, 262);
            MoveToEx(hdc, 430, 275, NULL);
            LineTo(hdc, 468, 282); //�����ʾƷ� ����
            MoveToEx(hdc, 470, 255, NULL);
            LineTo(hdc, 420, 272);
        }
        // �׸��⸦ ���� ��ǥ ���
        int left1 = 16;
        int top1 = 90;
        int right1 = rc.right - 16;
        int bottom1 = rc.bottom - 16;

        // �е��� ������ 8px�� �簢�� �׵θ� �׸���
        RECT rect1 = { left1, top1, right1, bottom1 };
        FrameRect(hdc, &rect1, (HBRUSH)GetStockObject(BLACK_BRUSH));

        int left2 = 8;
        int top2 = 8;
        int right2 = rc.right - 8;
        int bottom2 = rc.bottom - 8;

        // �е��� ������ 8px�� �簢�� �׵θ� �׸���
        RECT rect2 = { left2, top2, right2, bottom2 };
        FrameRect(hdc, &rect2, (HBRUSH)GetStockObject(BLACK_BRUSH));

        if (isRectangleMode && (button == 0))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            // �巡�� ���� ���� �׸���
            dragRect.left = min(startPoint.x, endPoint.x);
            dragRect.top = min(startPoint.y, endPoint.y);
            dragRect.right = max(startPoint.x, endPoint.x);
            dragRect.bottom = max(startPoint.y, endPoint.y);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
            FillRect(hdc, &dragRect, hBrush); // ��ũ�� ���� �׸���
            DeleteObject(hBrush);
        }
        else if (isRectangleMode && (button == 1))
        {
            RECT rect;
            GetClientRect(hwnd, &rect);

            HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255)); // ��ũ �귯�� ����
            FillRect(hdc, &dragRect, hBrush); // ��ũ�� ���� �׸���
            DeleteObject(hBrush);
        }
        else if (isCircleMode && isDrawingEnabled)
        {
            // �� �׸���
            HBRUSH hBrush = CreateSolidBrush(RGB(0, 0, 255)); // �Ķ��� �귯�� ����
            float radius = sqrt(pow(endPoint.x - startPoint.x, 2) + pow(endPoint.y - startPoint.y, 2)); // �� �� ������ �Ÿ��� ���������� ����
            Ellipse(hdc, startPoint.x - radius, startPoint.y - radius, startPoint.x + radius, startPoint.y + radius); // �� �׸���
            DeleteObject(hBrush);
        }
        else if (isCircleMode && CircleScale)
        {

        }
        else if (isRyanMode)
        {
            // ���̾� �׸���
            int ryanLeft = min(startPoint.x, endPoint.x);   // ���̾��� ���� X ��ǥ�� �巡�� ���������� ����
            int ryanTop = min(startPoint.y, endPoint.y);    // ���̾��� ��� Y ��ǥ�� �巡�� ���������� ����
            int ryanRight = min(startPoint.x, endPoint.x);    // ���̾��� ���� X ��ǥ�� �巡�� �������� ����
            int ryanBottom = max(startPoint.y, endPoint.y);   // ���̾��� �ϴ� Y ��ǥ�� �巡�� �������� ����


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