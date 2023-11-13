#include "yuhanCG.h"
#include <Windows.h>
#include <tchar.h>
#include <vector>

void DrawRyan(HDC hdc, const std::vector<POINT>& points) {
    // ���̾� �׸��� �ڵ�
    if (points.size() < 2) {
        return;  // �ּ��� �� ���� ���� �ʿ��մϴ�.
    }

    MoveToEx(hdc, points[0].x, points[0].y, NULL);
    for (size_t i = 1; i < points.size(); ++i) {
        LineTo(hdc, points[i].x, points[i].y);
    }
}
