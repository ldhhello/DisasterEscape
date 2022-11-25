#define _CRT_SECURE_NO_WARNINGS

#include "LoadGameWindow.h"
#include "Game.h"

void LoadGame_modal()
{
	//image_layer.clearImage(&image_layer, false);

	Image im = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 / 2, 2, 0, bitmap_game_load, true };

	//image_layer.appendImage(&image_layer, im, false);
	image_layer.images = &im;
	image_layer.imageCount = 1;

	image_layer.fadeIn(&image_layer, NULL);

	int cursor = 0;
	int print_pos = 0;

	int max_file = 3;

	int start_x = SCREEN_X * 16 / 2 - 600 - 300;

	while (true)
	{
		image_layer.startRender(&image_layer);

		for (int i = 0; i < 3; i++)
		{
			int k = print_pos + i;

			char buf[15];
			sprintf(buf, "½½·Ô %d", k + 1);

			if (cursor == k)
				printText(image_layer.bufferDC, start_x + 600 * i, 1150, start_x + 600 + 600 * i, 1150 + 75, "°­¿ø±³À°Æ°Æ°", 80, RGB(255, 0, 0), DT_CENTER, buf);
			else
				printText(image_layer.bufferDC, start_x + 600 * i, 1150, start_x + 600 + 600 * i, 1150 + 75, "°­¿ø±³À°Æ°Æ°", 80, RGB(255, 255, 255), DT_CENTER, buf);
		}

		image_layer.endRender(&image_layer);

		int ch = _getch();

		if (ch == LEFT)
		{
			if (cursor > 0)
				cursor--;
		}
		else if (ch == RIGHT)
		{
			if (cursor < max_file - 1)
				cursor++;
		}
		else if (ch == VK_ESCAPE)
			break;
		else if (ch == VK_RETURN || ch == VK_SPACE)
		{
			image_layer.fadeOut(&image_layer, NULL);

			Game_modal_load(cursor);
			break;
		}
	}

	image_layer.fadeOut(&image_layer, NULL);

	return 1;
}