#include "Include.h"

void printTextWithAngle(HDC hdc, int x, int y, char* fontName, int size, int weight, int angle, COLORREF textColor, int align, char* text) {
	if (weight == 0) weight = 900;
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, textColor);
	//SetTextAlign(hdc, align);

	x = (int)(x * RESOLUTION_MULTIPLIER);
	y = (int)(y * RESOLUTION_MULTIPLIER);
	TextOut(hdc, x, y, text, lstrlen(text));

	PAINTSTRUCT paint;
	EndPaint(hWnd, &paint);

	DeleteObject(font);
}

void printText(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, char* text)
{
	int weight = 1;
	int angle = 0;
	if (weight == 0) weight = 900;
	size = (int)(size * RESOLUTION_MULTIPLIER);
	const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
		0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	SelectObject(hdc, font);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, textColor);
	//SetTextAlign(hdc, align);

	left = (int)(left * RESOLUTION_MULTIPLIER);
	top = (int)(top * RESOLUTION_MULTIPLIER);
	right = (int)(right * RESOLUTION_MULTIPLIER);
	bottom = (int)(bottom * RESOLUTION_MULTIPLIER);
	//TextOut(hdc, x, y, text, lstrlen(text));
	RECT rect = { left, top, right, bottom };
	DrawText(hdc, text, -1, &rect, align);

	PAINTSTRUCT paint;
	EndPaint(hWnd, &paint);

	DeleteObject(font);
}