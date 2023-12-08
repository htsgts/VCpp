#pragma once
#define SHAPES_H

// 사각형을 그리는 함수 프로토타입
void DrawRectangle(HDC hdc, int startX, int startY, int endX, int endY);

// 원을 그리는 함수 프로토타입
void DrawCircle(HDC hdc, int startX, int startY, int endX, int endY);

// 보노보노를 그리는 함수 프로토타입
void DrawBonobono(HDC hdc);

// 라이언을 그리는 함수 프로토타입
void DrawRyan(HDC hdc, int left, int top, int right, int bottom);


