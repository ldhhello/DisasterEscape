#include "StartWindow.h"
#include "Game.h"

Image startwindow_image[3];

char* menu_text[] = {
	"�����ϱ�",
	"�ҷ�����",
	"���� ����"
};
int menu_cnt = 3;
int current_idx = 0;

void StartWindow_draw()
{
	//image_layer.renderAll(&image_layer);
	image_layer.startRender(&image_layer);

	RECT rect = { SCREEN_X*16/2 - 300, SCREEN_Y * 16 / 2 + 200, SCREEN_X * 16 / 2 + 300, SCREEN_Y * 16 / 2 + 600 };

	Rectangle_(image_layer.bufferDC, rect.left, rect.top, rect.right, rect.bottom);

	for (int i = 0; i < menu_cnt; i++)
	{
		COLORREF color = RGB(0, 0, 0);

		if (current_idx == i)
		{
			color = RGB(255, 0, 0);

			Rectangle_(image_layer.bufferDC, SCREEN_X*16 / 2 - 160, SCREEN_Y*16 / 2 + 220 + 120 * i,
				SCREEN_X*16 / 2 + 160, SCREEN_Y*16 / 2 + 300 + 120 * i);
		}

		printText(image_layer.bufferDC, SCREEN_X*16 / 2 - 200, SCREEN_Y*16 / 2 + 220 + 120*i, 
			SCREEN_X*16 / 2 + 200, SCREEN_Y*16 / 2 + 300 + 120*i,
			"���� ���", 60, color, DT_CENTER, menu_text[i]);
	}

	image_layer.endRender(&image_layer);
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
	if (current_idx == 0) // �����ϱ�
	{
		Game_modal();

		image_layer.imageCount = 1;
		image_layer.images = startwindow_image;

		StartWindow_draw();
	}
}