#include <windows.h>
#include <cmath>

HBRUSH hFaceBrush;  // ���� �׸��µ� ����� �귯��
HBRUSH hEyeBrush;   // ���� �׸��µ� ����� �귯��
HBRUSH hEarBrush;   // �͸� �׸��µ� ����� �귯��
HBRUSH hMouthBrush; // ���� �׸��µ� ����� �귯��

static HCURSOR hCrossCursor = LoadCursor(NULL, IDC_CROSS);
static HCURSOR hArrowCursor = LoadCursor(NULL, IDC_ARROW);

POINT startPoint = { 0 };
POINT endPoint = { 0 };
BOOL isRyanMode = FALSE;

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
