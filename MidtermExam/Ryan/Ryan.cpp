#include "yuhanCG.h"
#include <Windows.h>
#include <tchar.h>
#include <vector>

void DrawRyan(HDC hdc, const std::vector<POINT>& points) {
    // 라이언 그리기 코드
    if (points.size() < 2) {
        return;  // 최소한 두 개의 점이 필요합니다.
    }

    MoveToEx(hdc, points[0].x, points[0].y, NULL);
    for (size_t i = 1; i < points.size(); ++i) {
        LineTo(hdc, points[i].x, points[i].y);
    }
}
