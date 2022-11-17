#include "StartWindow.h"
#include "Game.h"

Image startwindow_image[3];

char* menu_text[] = {
	"시작하기",
	"불러오기",
	"게임 정보"
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

void StartWindow_select();

void StartWindow_modal()
{
	Image a = { "", 0, 0, 0, 0, bitmap_start_screen };
	//Image b = { "D:\\start.bmp", 400, 740 };
	startwindow_image[0] = a;
	//startwindow_image[1] = b;

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

			//printf("selected #%d", current_idx);

			StartWindow_select();
		}
	}
}

void StartWindow_select()
{
	if (current_idx == 0) // 시작하기
	{
		Game_modal();

		image_layer.imageCount = 1;
		image_layer.images = startwindow_image;

		StartWindow_draw();
	}
}