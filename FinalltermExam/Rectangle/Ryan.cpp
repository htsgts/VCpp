#include <windows.h>
#include <cmath>

HBRUSH hFaceBrush;  // 얼굴을 그리는데 사용할 브러시
HBRUSH hEyeBrush;   // 눈을 그리는데 사용할 브러시
HBRUSH hEarBrush;   // 귀를 그리는데 사용할 브러시
HBRUSH hMouthBrush; // 입을 그리는데 사용할 브러시

static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);

POINT startPoint = { 0 };
POINT endPoint = { 0 };
BOOL isRyanMode = FALSE;

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
