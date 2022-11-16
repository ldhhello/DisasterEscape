//#include "StartWindow.h"
#include "Include.h"

Image startwindow_image[3];

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

char* menu_text[] = {
	"시작하기",
	"게임 정보",
	"testst!!!!!"
};
int menu_cnt = 3;
int current_idx = 0;

void StartWindow_draw()
{
	image_layer.renderAll(&image_layer);

	RECT rect = { WINDOW_WIDTH / 2 - 150, WINDOW_HEIGHT / 2 + 100, WINDOW_WIDTH / 2 + 150, WINDOW_HEIGHT / 2 + 300 };

	Rectangle(image_layer._consoleDC, rect.left, rect.top, rect.right, rect.bottom);

	for (int i = 0; i < menu_cnt; i++)
	{
		COLORREF color = RGB(0, 0, 0);

		if (current_idx == i)
		{
			color = RGB(255, 0, 0);

			Rectangle(image_layer._consoleDC, WINDOW_WIDTH / 2 - 80, WINDOW_HEIGHT / 2 + 110 + 60 * i, WINDOW_WIDTH / 2 + 80, WINDOW_HEIGHT / 2 + 150 + 60 * i);
		}

		printText(image_layer._consoleDC, WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 + 110 + 60*i, WINDOW_WIDTH / 2 + 100, WINDOW_HEIGHT / 2 + 150 + 60*i,
			"맑은 고딕", 30, color, DT_CENTER, menu_text[i]);
	}
}

void StartWindow_modal()
{
	Image a = { "D:\\test3.bmp", 0, 0 };
	Image b = { "D:\\start.bmp", 400, 740 };
	startwindow_image[0] = a;
	startwindow_image[1] = b;

	image_layer.imageCount = 1;
	image_layer.images = startwindow_image;

	StartWindow_draw();

	while (1)
	{
		int ch = _getch();

		if (ch == DOWN)
		{
			current_idx++;
			if (current_idx >= menu_cnt)
				current_idx = menu_cnt - 1;

			StartWindow_draw();
		}
		else if (ch == UP)
		{
			current_idx--;
			if (current_idx < 0)
				current_idx = 0;

			StartWindow_draw();
		}
		else if (ch == VK_SPACE || ch == VK_RETURN) // select
		{
			image_layer.fadeOut(&image_layer, NULL);

			printf("selected #%d", current_idx);
		}
	}
}