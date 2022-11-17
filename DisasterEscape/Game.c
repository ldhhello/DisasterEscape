#include "Game.h"

Image game_image[1000];

void Game_append_image(Image im, bool redraw)
{
	game_image[image_layer.imageCount] = im;
	image_layer.imageCount++;

	if(redraw)
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
	Game_append_image(im, true);

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
			Sleep(50);

			ignored = false;
		}
		else
			ignored = true;
	}

	free(now_str);

	_getch();

	Game_erase_image();
}

int map_x = 0, map_y = 0;
int player_x = 5, player_y = 5;

int map_[100][100] = {
	{ 0, 0, 0, 0, 0},
	{ 0, 1, 0, 1, 0},
	{ 0, 0, 0, 0, 0},
	{ 0, 1, 0, 1, 0},
	{ 0, 0, 1, 0, 0},
};
int max_x = 100, max_y = 100;

int next_start_pos(int prev, int cursor, int screen_size, int max_pos)
{
	int s = prev + 3, e = prev + screen_size - 3;

	if (s <= cursor && cursor <= e)
		return prev;

	int res = 0;

	if (s > cursor)
		res = cursor-3;
	else if (cursor > e)
		res = cursor - screen_size + 3;
	
	if (res < 0)
		return 0;
	if (res > max_pos - screen_size)
		return max_pos - screen_size;

	return res;
}

void Game_modify_player_pos()
{
	if (player_x < 0)
		player_x = 0;
	if (player_x >= max_x)
		player_x = max_x;
	if (player_y < 0)
		player_y = 0;
	if (player_y >= max_x)
		player_y = max_x;

	map_x = next_start_pos(map_x, player_x, SCREEN_X / 8-1, max_x);
	map_y = next_start_pos(map_y, player_y, SCREEN_Y / 8-1, max_y);
}

void Game_print_map()
{
	image_layer.imageCount = 0;

	Image a = { "", 0, 0, 0, 0, bitmap_jandi };

	for (int y = 0; y < SCREEN_Y/8+1; y++)
	{
		for (int x = 0; x < SCREEN_X / 8 + 1; x++)
		{
			int ax = map_x + x;
			int ay = map_y + y;

			if (map_[ay][ax] == 0)
			{
				a.x = x * 16 * 8;
				a.y = y * 16 * 8;
				Game_append_image(a, false);
			}
		}
	}

	a.bitmap = bitmap_player;
	a.x = (player_x-map_x) * 16 * 8;
	a.y = (player_y-map_y) * 16 * 8;
	a.scale = 8;

	Game_append_image(a, false);

	image_layer.renderAll(&image_layer);
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

	Game_print_map();
	Sleep(1000);

	for (;;)
	{
		if (_kbhit())
		{
			int ch = _getch();

			if (ch == UP)
			{
				player_y--;
			}
			else if (ch == DOWN)
			{
				player_y++;
			}
			else if (ch == LEFT)
			{
				player_x--;
			}
			else if (ch == RIGHT)
			{
				player_x++;
			}
			Game_modify_player_pos();

			Game_print_map();
		}

		//Sleep(50);
	}

	Sleep(3000);
}