#include "Game.h"
#include "Structure.h"

#include "SceneDimigo.h"

Image game_image[1500];

#ifdef _DEBUG
bool _trace(TCHAR* format, ...)
{
	TCHAR buffer[1000];

	va_list argptr;
	va_start(argptr, format);
	wvsprintf(buffer, format, argptr);
	va_end(argptr);

	OutputDebugString(buffer);

	return true;
}
#endif

#ifdef _DEBUG
bool _trace(TCHAR* format, ...);
#define TRACE _trace
#else
#define TRACE false && _trace
#endif

void Game_speech_nowait(const char* str)
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
			int a = _getch();

			if (a == 224)
				_getch();

			memcpy(now_str, str, sz + 1);

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

			printText(image_layer.bufferDC, 10, 52 * 16 + 10, 180 * 16 - 10, 96 * 16 - 10, "맑은 고딕", 150, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);
			Sleep(45);

			ignored = false;
		}
		else
			ignored = true;
	}

	free(now_str);
}

void Game_speechbubble(const char* str)
{
	Game_speech_nowait(str);

	int a = _getch();

	if (a == 224)
		_getch();

	//Game_erase_image();
	image_layer.eraseImage(&image_layer, true);
}

int map_x = 0, map_y = 0;
int player_x = 10, player_y = 10;

// 이거는 스택처럼 사용됨
int last_x_arr[100];
int last_y_arr[100];

int last_arr_sz = 0;

//int map_[100][100] = {
//	{ 0, 0, 0, 0, 0},
//	{ 0, 1, 0, 1, 0},
//	{ 0, 0, 0, 0, 0},
//	{ 0, 1, 0, 1, 0},
//	{ 0, 0, 1, 0, 0},
//};
//int max_x = 100, max_y = 100;
//
//Structure structure[100];
//int structure_cnt;

int** map_;
int max_x, max_y;

Structure* structure;
int structure_cnt;

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

void Game_print_map(bool fade_in)
{
	image_layer.imageCount = 0;

	Image a = { "", 0, 0, 0, 0, bitmap_tile[0] };

	for (int y = 0; y < SCREEN_Y/8+1; y++)
	{
		for (int x = 0; x < SCREEN_X / 8 + 1; x++)
		{
			int ax = map_x + x;
			int ay = map_y + y;

			/*if (map_[ay][ax] == 0)
			{
				a.x = x * 16 * 8;
				a.y = y * 16 * 8;
				image_layer.appendImage(&image_layer, a, false);
			}*/

			a.x = x * 16 * 8;
			a.y = y * 16 * 8;
			a.bitmap = bitmap_tile[map_[ay][ax]];

			image_layer.appendImage(&image_layer, a, false);
		}
	}

	for (int i = 0; i < structure_cnt; i++)
	{
		if (structure[i].is_hide)
			continue;

		if (a.bitmap == NULL)
			continue;

		a.bitmap = structure[i].bitmap;
		a.x = (structure[i].x - map_x) * 16 * 8;
		a.y = (structure[i].y - map_y) * 16 * 8;

		a.scale = structure[i].scale;

		image_layer.appendImage(&image_layer, a, false);
	}

	a.bitmap = bitmap_player;
	a.x = (player_x-map_x) * 16 * 8;
	a.y = (player_y-map_y) * 16 * 8;
	a.scale = 8;

	image_layer.appendImage(&image_layer, a, false);

	if (fade_in)
		image_layer.fadeIn(&image_layer, NULL);
	else
		image_layer.renderAll(&image_layer);

	//TRACE("image_layer size: %d\n", image_layer.imageCount);
}

int Game_check_block()
{
	for (int i = 0; i < structure_cnt; i++)
	{
		if (structure[i].is_hide)
			continue;

		if (structure[i].passable)
			continue;

		if (structure[i].x <= player_x && player_x < structure[i].x + structure[i].width &&
			structure[i].y <= player_y && player_y < structure[i].y + structure[i].height)
			return i;
	}

	return -1;
}

int Game_modal_select_box(char (*str)[100], int cnt)
{
	int last_image_cnt = image_layer.imageCount;

	int now = 0;

	//Image im = {"", ((player_x-map_x)*16*8) + 10, ((player_y-map_y)*16*8) + 10, 0, 0,}
	//image_layer.appendImage(&image_layer, )

	while (true)
	{
		image_layer.startRender(&image_layer);

		Rectangle_(image_layer.bufferDC, ((player_x - map_x + 1) * 16 * 8) - 40, ((player_y - map_y + 1) * 16 * 8) - 40,
			((player_x - map_x + 1) * 16 * 8) + 160, ((player_y - map_y + 1) * 16 * 8) + 40 * cnt - 40);

		for (int i = 0; i < cnt; i++)
		{
			COLORREF color = RGB(0, 0, 0);
			if (i == now)
				color = RGB(255, 0, 0);

			printText(image_layer.bufferDC, ((player_x - map_x + 1) * 16 * 8) - 40, ((player_y - map_y + 1) * 16 * 8) + 40 * i - 40,
				((player_x - map_x + 1) * 16 * 8) + 160, ((player_y - map_y + 1) * 16 * 8) + 40 * i,
				"맑은 고딕", 40, color, DT_CENTER, str[i]);
		}

		image_layer.endRender(&image_layer);

		int ch = _getch();

		if (ch == UP && now > 0)
			now--;
		else if (ch == DOWN && now < cnt - 1)
			now++;
		else if (ch == VK_SPACE || ch == VK_RETURN)
		{
			image_layer.renderAll(&image_layer);
			return now;
		}
		else if (ch == VK_ESCAPE)
		{
			image_layer.renderAll(&image_layer);
			return -1;
		}
	}
	//image_layer.renderAll(&image_layer);
}

int Game_modal_select_box_speech(char* speech, char(*str)[100], int cnt)
{
	Game_speech_nowait(speech);

	int last_image_cnt = image_layer.imageCount;

	int now = 0;

	//Image im = {"", ((player_x-map_x)*16*8) + 10, ((player_y-map_y)*16*8) + 10, 0, 0,}
	//image_layer.appendImage(&image_layer, )

	while (true)
	{
		image_layer.startRender(&image_layer);

		printText(image_layer.bufferDC, 10, 52 * 16 + 10, 180 * 16 - 10, 96 * 16 - 10, "맑은 고딕", 150, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, speech);

		// 180 * 16 - 10 - 200, 52 * 16 - 10 - 200
		Rectangle_(image_layer.bufferDC, 180 * 16 - 210, 52 * 16 - 10 - 40*cnt,
			180 * 16 - 10, 52 * 16 - 10);

		for (int i = 0; i < cnt; i++)
		{
			COLORREF color = RGB(0, 0, 0);
			if (i == now)
				color = RGB(255, 0, 0);

			printText(image_layer.bufferDC, 180 * 16 - 210, 52*16 - 10 - 40*cnt + 40 * i,
				180*16 - 10, 52*16 - 10 - 40*cnt + 40 * i + 40,
				"맑은 고딕", 40, color, DT_CENTER, str[i]);
		}

		image_layer.endRender(&image_layer);

		int ch = _getch();

		if (ch == UP && now > 0)
			now--;
		else if (ch == DOWN && now < cnt - 1)
			now++;
		else if (ch == VK_SPACE || ch == VK_RETURN)
		{
			image_layer.renderAll(&image_layer);
			return now;
		}
		else if (ch == VK_ESCAPE)
		{
			image_layer.renderAll(&image_layer);
			return -1;
		}
	}
	//image_layer.renderAll(&image_layer);
}

void (*Game_on_structure_active)(int st, int dir);
void (*Game_on_start)();

void Game_change_scene(Scene sc, bool is_enter)
{
	image_layer.fadeOut(&image_layer, NULL);

	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	Game_on_structure_active = sc.on_structure_active;
	Game_on_start = sc.on_start;

	if (is_enter)
	{
		last_x_arr[last_arr_sz] = player_x;
		last_y_arr[last_arr_sz] = player_y;
		last_arr_sz++;

		player_x = 3; player_y = 3;
		map_x = 0; map_y = 0;
	}
	else
	{
		player_x = last_x_arr[last_arr_sz - 1];
		player_y = last_y_arr[last_arr_sz - 1];
		last_arr_sz--;

		Game_modify_player_pos();
	}

	Sleep(1000);

	Game_print_map(true);

	Game_on_start();
}

void Game_modal()
{
	Sleep(500);

	Scene sc = SceneDimigo_load();

	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	Game_on_structure_active = sc.on_structure_active;
	Game_on_start = sc.on_start;

	Game game;
	memset(&game, 0, sizeof(Game));

	Image a = { "", 0, 0, 2, 0, bitmap_loading_none };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.renderAll(&image_layer);

	Sleep(1000);

	game_image[0].bitmap = bitmap_loading_image;

	image_layer.renderAll(&image_layer);

	Sleep(2000);

	image_layer.clearImage(&image_layer, true);

	Sleep(1000);

	Game_modify_player_pos();

	//Game_speechbubble("안녕하세요!, Hello!d sfdfsdfsdf sdfdfsf dfsdfs dfsdfsd fsdfsdf");

	Game_print_map(true);
	//Sleep(1000);

	Game_on_start();

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

			int check_st = 0;
			if ((check_st = Game_check_block()) != -1)
			{
				player_x = last_x;
				player_y = last_y;

				if (structure[check_st].on_active != NULL)
					structure[check_st].on_active(check_st, ch);
				else
					Game_on_structure_active(check_st, ch);
			}

			Game_modify_player_pos();

			Game_print_map(false);
		}

		//Sleep(50);
	}

	Sleep(3000);
}