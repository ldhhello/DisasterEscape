#include "Game.h"
#include "Structure.h"

#include "SceneDimigo.h"

Image game_image[1500];

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
			Sleep(40);

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
int player_x = 2, player_y = 3;

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
		else if (ch == DOWN && now < cnt-1)
			now++;
		else if (ch == VK_SPACE || ch == VK_RETURN)
		{
			image_layer.renderAll(&image_layer);
			return now;
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
	}
	//image_layer.renderAll(&image_layer);
}

void Game_modal()
{
	/*Structure s = {3, 3, 4, 8, bitmap_house};
	structure[0] = s;
	s.x = 10; s.y = 3;
	structure[1] = s;
	s.x = 17; s.y = 3;
	structure[2] = s;
	s.x = 24; s.y = 3;
	structure[3] = s;
	structure_cnt = 4;*/

	Scene sc = SceneDimigo_load();

	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	Game game;
	memset(&game, 0, sizeof(Game));

	Image a = { "", 0, 0, 2, 0, bitmap_loading_image };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.renderAll(&image_layer);

	Sleep(3000);

	image_layer.clearImage(&image_layer, true);

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

			if (ch == UP && player_y == last_y && player_y != 0)
				//Game_speechbubble("들어가면 안 될 것 같다!");
			{
				char str[4][100] = {
					"들어가기",
					"도망가기",
					"잡아먹기",
					"사용하기"
				};

				switch (Game_modal_select_box_speech("집이다! 들어갈까?", str, 4))
				{
				case 0:
					Game_speechbubble("들어가는데 실패했다!");
					break;
				case 1:
					Game_speechbubble("도망가는데 실패했다!");
					break;
				case 2:
					Game_speechbubble("집을 잡아먹는다고??? 난 못 먹어..");
					break;
				case 3:
					Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
					break;
				}
			}

			Game_print_map();
		}

		//Sleep(50);
	}

	Sleep(3000);
}