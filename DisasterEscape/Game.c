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
	Image im = { "", 0, 52 * 16, 0, 0, bitmap_speech_bubble };
	Game_append_image(im);

	int sz = strlen(str);

	char* now_str = malloc(sz + 1);

	// 글자 하나씩 하나씩 출력하는 코드
	// 1바이트씩 해도 되지 않냐고 할 수 있지만 그러면 문제가 한글이 2바이트다! (ansi 인코딩 기준)
	// 그래서 그거 해결하기 위해 이런 코드를 구현했다!!
	bool ignored = false;

	for (int i = 0; i < sz; i++)
	{
		now_str[i] = str[i];
		now_str[i + 1] = 0;

		if (now_str[i] >= 0 || ignored)
		{
			//image_layer.renderAll(&image_layer);
			image_layer.startRender(&image_layer);

			printText(image_layer.bufferDC, 10, 52*8 + 10, 180*8 - 10, 96*8 - 10, "맑은 고딕", 100, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);
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

	Image a = { "", 0, 0, 0, 0, bitmap_loading_image };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.renderAll(&image_layer);

	Sleep(3000);

	Game_speechbubble("안녕하세요!, Hello!d sfdfsdfsdf sdfdfsf dfsdfs dfsdfsd fsdfsdf");

	Sleep(3000);
}