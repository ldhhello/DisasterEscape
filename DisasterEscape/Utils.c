// 전체 시스템에서 유용하게 쓸 수 있는 함수들을 모아놓은 코드!
// 여기있는 모든 함수들은 Include.h 에서 extern 한다

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

// Rectangle는 시스템의 DPI 설정에 따라 약간 다르게 나온다!
// 근데 얘는 DPI 설정에 상관없이 잘 나온다!!!
void Rectangle_(HDC hdc, int left, int top, int right, int bottom)
{
	Rectangle(hdc, left * RESOLUTION_MULTIPLIER, top * RESOLUTION_MULTIPLIER,
		right * RESOLUTION_MULTIPLIER, bottom * RESOLUTION_MULTIPLIER);
}

// 구현 포기..ㅠㅠ DrawText DT_CALCRECT가 잘 안 된다
// 그래도 수식으로 해도 그럭저럭 잘 작동한다!
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

// 얘를 쓰면 DT_LEFT, DT_RIGHT 같은걸 지정해서 가운데정렬, 왼쪽정렬, 오른쪽정렬 이런걸 할수있다!
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

// 위에 printText와 같지만 얘는 wchar_t*를 받는다 (text 가 const char* 지만 사실 const wchar_t*를 받아야 잘 돌아간다)
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

// 현재 커서 (플레이어) 의 위치에 따라 보이는 화면 영역이 어디부터 어디까지인지 계산한다!
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

// Sleep을 한 뒤 입력 버퍼를 날려버린다!
// sleep_ 정의가 ImageLayer에 없어서 컴파일에 약간 warning이 뜨긴 하는데
// C는 생각보다 컴파일에 관대해서 extern이 없어도 암시적으로 지가 extern해줘서
// 알아서 돌아가긴 하는것같다..
// 원래 이렇게하면 안되는데 되니까 놔두는걸로!!
int sleep_(int ms)
{
	Sleep(ms);
	
	while (_kbhit()) _getch();

	return 0;
}