#include "Game.h"

Image game_image[20];

void Game_append_image(Image im)
{
	game_image[image_layer.imageCount] = im;
	image_layer.imageCount++;

	image_layer.renderAll(&image_layer);
}

void Game_erase_image()
{
	image_layer.imageCount--;

	image_layer.renderAll(&image_layer);
}

void Game_speechbubble(const char* str)
{
	Image im = { "D:\\speechbubble.bmp", 0, 52 * 16 };
	Game_append_image(im);

	int sz = strlen(str);

	char* now_str = malloc(sz + 1);

	bool ignored = false;

	for (int i = 0; i < sz; i++)
	{
		now_str[i] = str[i];
		now_str[i + 1] = 0;

		if (now_str[i] >= 0 || ignored)
		{
			image_layer.renderAll(&image_layer);
			printText(image_layer._consoleDC, 10, 52*8 + 10, 180*8 - 10, 96*8 - 10, "∏º¿∫ ∞ÌµÒ", 100, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);
			Sleep(120);

			ignored = false;
		}
		else
			ignored = true;
	}

	free(now_str);

	_getch();

	Game_erase_image();
}

void Game_modal()
{
	Game game;
	memset(&game, 0, sizeof(Game));

	Image a = { "D:\\loading.bmp", 0, 0 };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.renderAll(&image_layer);

	Sleep(3000);

	Game_speechbubble("æ»≥Á«œººø‰!, Hello!d sfdfsdfsdf sdfdfsf dfsdfs dfsdfsd fsdfsdf");

	Sleep(3000);
}