#include "StartWindow.h"
#include "Game.h"
#include "GameInfo.h"
#include "LoadGameWindow.h"

#include "Music.h"

Image startwindow_image[12];

char* menu_text[] = {
	"시작하기",
	"불러오기",
	"게임 정보"
};
int menu_cnt = 3;
int current_idx = 0;

void StartWindow_draw()
{
	image_layer.imageCount = 1;

	RECT rect = { SCREEN_X*16/2 - 300, SCREEN_Y * 16 / 2 + 200, SCREEN_X * 16 / 2 + 300, SCREEN_Y * 16 / 2 + 600 };

	Image im = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 / 2 + 200, 1.5, 0, bitmap_button[0][0], true };

	for (int i = 0; i < menu_cnt; i++)
	{
		im.bitmap = bitmap_button[i][current_idx == i ? 1 : 0];

		image_layer.appendImage(&image_layer, im, false);

		im.y += 120;
	}

	image_layer.renderAll(&image_layer);
}

void StartWindow_select();

void StartWindow_modal()
{
	Image a = { "", 0, 0, 2, 0, bitmap_start_screen };
	startwindow_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = startwindow_image;

	StartWindow_draw();

	Music_set_background(MAKEINTRESOURCE(IDR_WAVE_MAINBGM));
	//PlaySound(MAKEINTRESOURCE(IDR_WAVE_MAINBGM), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);

	time_t last_time = time(NULL);

	while (1)
	{
		if (_kbhit())
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
}

void StartWindow_select()
{
	if (current_idx == 0) // 시작하기
	{
		Music_stop_background();

		Game_modal_new();
		Music_set_background(MAKEINTRESOURCE(IDR_WAVE_MAINBGM));
	}
	else if (current_idx == 1)
	{
		LoadGame_modal();

		Music_set_background(MAKEINTRESOURCE(IDR_WAVE_MAINBGM));
	}
	else if (current_idx == 2)
	{
		GameInfo_modal();
	}

	image_layer.imageCount = 1;
	image_layer.images = startwindow_image;

	image_layer.fadeIn(&image_layer, NULL);
	StartWindow_draw();
}