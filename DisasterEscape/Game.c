#include "Game.h"
#include "Structure.h"

Image game_image[1500];

void Game_speechbubble(const char* str)
{
	Image im = { "", 0, 52 * 16, 0, 0, bitmap_speech_bubble };
	//Game_append_image(im, true);
	image_layer.appendImage(&image_layer, im, true);

	int sz = strlen(str);

	char* now_str = malloc(sz + 1);

	// 글자 하나씩 하나씩 출력하는 코드
	// 1바이트씩 해도 되지 않냐고 할 수 있지만 그러면 문제가 한글이 2바이트다! (ansi 인코딩 기준)
	// 그래서 그거 해결하기 위해 이런 코드를 구현했다!!
	bool ignored = false;

	for (int i = 0; i < sz; i++)
	{
		if (_kbhit())
		{
			_getch();

			memcpy(now_str, str, sz+1);

			image_layer.startRender(&image_layer);

			printText(image_layer.bufferDC, 10, 52 * 16 + 10, 180 * 16 - 10, 96 * 16 - 10, "맑은 고딕", 150, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);
			
			break;
		}
		now_str[i] = str[i];
		now_str[i + 1] = 0;

		if (now_str[i] >= 0 || ignored)
		{
			//image_layer.renderAll(&image_layer);
			image_layer.startRender(&image_layer);

			printText(image_layer.bufferDC, 10, 52*16 + 10, 180*16 - 10, 96*16 - 10, "맑은 고딕", 150, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);
			Sleep(40);

			ignored = false;
		}
		else
			ignored = true;
	}

	free(now_str);

	_getch();

	//Game_erase_image();
	image_layer.eraseImage(&image_layer, true);
}

int map_x = 0, map_y = 0;
int player_x = 2, player_y = 3;

int map_[100][100] = {
	{ 0, 0, 0, 0, 0},
	{ 0, 1, 0, 1, 0},
	{ 0, 0, 0, 0, 0},
	{ 0, 1, 0, 1, 0},
	{ 0, 0, 1, 0, 0},
};
int max_x = 100, max_y = 100;

Structure structure[100];
int structure_cnt;

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
				image_layer.appendImage(&image_layer, a, false);
			}
		}
	}

	for (int i = 0; i < structure_cnt; i++)
	{
		a.bitmap = structure[i].bitmap;
		a.x = (structure[i].x - map_x) * 16 * 8;
		a.y = (structure[i].y - map_y) * 16 * 8;

		image_layer.appendImage(&image_layer, a, false);
	}

	a.bitmap = bitmap_player;
	a.x = (player_x-map_x) * 16 * 8;
	a.y = (player_y-map_y) * 16 * 8;
	a.scale = 8;

	image_layer.appendImage(&image_layer, a, false);

	image_layer.renderAll(&image_layer);
}

bool Game_check_block()
{
	for (int i = 0; i < structure_cnt; i++)
	{
		if (structure[i].x <= player_x && player_x < structure[i].x + structure[i].width &&
			structure[i].y <= player_y && player_y < structure[i].y + structure[i].height)
			return true;
	}

	return false;
}

void Game_modal()
{
	Structure s = { 3, 3, 4, 8, bitmap_house };
	structure[0] = s;
	s.x = 10; s.y = 3;
	structure[1] = s;
	s.x = 17; s.y = 3;
	structure[2] = s;
	s.x = 24; s.y = 3;
	structure[3] = s;
	structure_cnt = 4;

	Game game;
	memset(&game, 0, sizeof(Game));

	Image a = { "", 0, 0, 2, 0, bitmap_loading_image };
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
			int last_x = player_x, last_y = player_y;

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

			if (Game_check_block())
			{
				player_x = last_x;
				player_y = last_y;
			}

			Game_modify_player_pos();

			if (ch == UP && player_y == last_y)
				Game_speechbubble("들어가면 안 될 것 같다!");

			Game_print_map();
		}

		//Sleep(50);
	}

	Sleep(3000);
}