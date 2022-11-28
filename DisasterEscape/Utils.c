// ��ü �ý��ۿ��� �����ϰ� �� �� �ִ� �Լ����� ��Ƴ��� �ڵ�!
// �����ִ� ��� �Լ����� Include.h ���� extern �Ѵ�

#include "Include.h"

// extern on Include.h

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

// Rectangle�� �ý����� DPI ������ ���� �ణ �ٸ��� ���´�!
// �ٵ� ��� DPI ������ ������� �� ���´�!!!
void Rectangle_(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left * RESOLUTION_MULTIPLIER, top * RESOLUTION_MULTIPLIER,
		right * RESOLUTION_MULTIPLIER, bottom * RESOLUTION_MULTIPLIER);
}

// ���� ����..�Ф� DrawText DT_CALCRECT�� �� �� �ȴ�
// �׷��� �������� �ص� �׷����� �� �۵��Ѵ�!
int getTextWidth(HDC hdc, char* fontName, int size, char* text)
{
	//int weight = 1;
	//int angle = 0;
	//if (weight == 0) weight = 900;
	//size = (int)(size * RESOLUTION_MULTIPLIER);
	//const HFONT font = CreateFont(size, 0, angle, 0, weight, 0, 0, 0, HANGEUL_CHARSET,
	//	0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT(fontName));

	//SelectObject(hdc, font);
	//SetBkMode(hdc, TRANSPARENT);
	////SetTextAlign(hdc, align);
	//
	////TextOut(hdc, x, y, text, lstrlen(text));
	////RECT rect = {0, 0, 0, 0};
	////DrawText(hdc, text, -1, &rect, DT_CALCRECT);
	//SIZE sz;
	//int a = GetTextExtentPointA(hdc, text, strlen(text), &sz);

	//PAINTSTRUCT paint;
	//EndPaint(hWnd, &paint);

	//DeleteObject(font);

	//return sz.cx / RESOLUTION_MULTIPLIER;

	return strlen(text) * 27;
}

// �긦 ���� DT_LEFT, DT_RIGHT ������ �����ؼ� �������, ��������, ���������� �̷��� �Ҽ��ִ�!
void printText(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, const char* text)
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

// ���� printText�� ������ ��� wchar_t*�� �޴´� (text �� const char* ���� ��� const wchar_t*�� �޾ƾ� �� ���ư���)
void printTextW(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, const char* text)
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
	DrawTextW(hdc, text, -1, &rect, align);

	PAINTSTRUCT paint;
	EndPaint(hWnd, &paint);

	DeleteObject(font);
}

// ���� Ŀ�� (�÷��̾�) �� ��ġ�� ���� ���̴� ȭ�� ������ ������ ���������� ����Ѵ�!
int next_start_pos(int prev, int cursor, int screen_size, int max_pos)
{
	int s = prev + 3, e = prev + screen_size - 3;

	if (s <= cursor && cursor <= e)
		return prev;

	int res = 0;

	if (s > cursor)
		res = cursor - 3;
	else if (cursor > e)
		res = cursor - screen_size + 3;

	if (res < 0)
		return 0;
	if (res > max_pos - screen_size)
		return max_pos - screen_size;

	return res;
}

// Sleep�� �� �� �Է� ���۸� ����������!
// sleep_ ���ǰ� ImageLayer�� ��� �����Ͽ� �ణ warning�� �߱� �ϴµ�
// C�� �������� �����Ͽ� �����ؼ� extern�� ��� �Ͻ������� ���� extern���༭
// �˾Ƽ� ���ư��� �ϴ°Ͱ���..
// ���� �̷����ϸ� �ȵǴµ� �Ǵϱ� ���δ°ɷ�!!
int sleep_(int ms)
{
	Sleep(ms);
	
	while (_kbhit()) _getch();

	return 0;
}