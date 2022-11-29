#define _CRT_SECURE_NO_WARNINGS

#include "Game.h"
#include "Structure.h"

#include "SceneDimigo.h"
#include "SceneCafeteria.h"
#include "SceneBongwan.h"
#include "SceneGangdang.h"
#include "SceneHealthjang.h"
#include "SceneSingwan.h"
#include "SceneBiggangdang.h"
#include "SceneHakbonggwan.h"
#include "SceneMaejom.h"

#include "Music.h"
#include "SaveFile.h"

Image game_image[1500];

int Game_return_val = -1;

int player_idx = 0; // 플레이어 사진 뭐띄울지

// Include.h에 정의된거랑 같은 순서임
Scene (*scene_load_function[])() = {
	NULL, SceneDimigo_load, SceneCafeteria_load, SceneBongwan_load,
	SceneGangdang_load, SceneHealthjang_load, SceneSingwan_load,
	SceneBiggangdang_load, SceneHakbonggwan_load,
	SceneMaejom_load
};

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

// 말풍선 띄우는 함수
// 얘는 말풍선만 딱 띄우고 그대로 종료된다!
// is_wide가 참이면 str를 유니코드로 (wchar_t*로) 읽는다
void Game_speech_nowait(const char* str, bool is_arrow, bool is_wide, int bubble_type)
{
	HBITMAP bubble_image[] = { bitmap_speech_bubble, bitmap_speech_bubble_ldh, bitmap_speech_bubble_ziaoming };

	Image im = { "", 40, 60 * 16, 2, 0, bubble_image[bubble_type]};
	//Game_append_image(im, true);
	image_layer.appendImage(&image_layer, im, true);

	int sz = strlen(str);

	if (is_wide)
		sz = lstrlenW(str) * 2;

	char* now_str = malloc(sz + 2);

	// 글자 하나씩 하나씩 출력하는 코드
	// 1바이트씩 해도 되지 않냐고 할 수 있지만 그러면 문제가 한글이 2바이트다! (ansi 인코딩 기준)
	// 그래서 그거 해결하기 위해 이런 코드를 구현했다!!
	bool ignored = false;

	void (*print_text)(HDC, int, int, int, int, char*, int, COLORREF, int, const char*) = printText;

	if (is_wide)
		print_text = printTextW;

	for (int i = 0; i < sz; i++)
	{
		if (_kbhit())
		{
			int a = _getch();

			if (a == 224)
				_getch();

			memcpy(now_str, str, sz + 1);

			Image im = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 - 70, 1, 0, bitmap_arrow, true };
			if(is_arrow)
				image_layer.appendImage(&image_layer, im, false);

			image_layer.startRender(&image_layer);

			print_text(image_layer.bufferDC, 100, 70 * 16 + 20, 180 * 16 -85, 96 * 16 - 20, "강원교육튼튼", 54, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);

			break;
		}
		now_str[i] = str[i];
		now_str[i + 1] = 0;
		now_str[i + 2] = 0; // for wide string

		if ((!is_wide && now_str[i] >= 0) || ignored)
		{
			//image_layer.renderAll(&image_layer);

			if (i == sz - 1 && is_arrow)
			{
				Image im = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 - 70, 1, 0, bitmap_arrow, true };
				image_layer.appendImage(&image_layer, im, false);
			}

			image_layer.startRender(&image_layer);

			print_text(image_layer.bufferDC, 100, 70 * 16 + 20, 180 * 16 - 85, 96 * 16 - 20, "강원교육튼튼", 54, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, now_str);

			image_layer.endRender(&image_layer);
			Sleep(45);

			ignored = false;
		}
		else
			ignored = true;
	}

	free(now_str);
}

// 기본 말풍선 띄우는 함수!
void Game_speechbubble(const char* str)
{
	Game_speech_nowait(str, true, false, 0);

	int a = _getch();

	if (a == 224)
		_getch();

	image_layer.eraseImage(&image_layer, false);
	image_layer.eraseImage(&image_layer, true);
}

// ziaoming 말풍선 띄우는 함수! (얘는 중국어를 띄워야 해서 약간 구현이 다르다!)
void Game_speechbubble_ziaoming(const wchar_t* str)
{
	Game_speech_nowait(str, true, true, 2);

	int a = _getch();

	if (a == 224)
		_getch();

	image_layer.eraseImage(&image_layer, false);
	image_layer.eraseImage(&image_layer, true);
}

// 동현이 말풍선 띄우는 함수!
void Game_speechbubble_ldh(const char* str)
{
	Game_speech_nowait(str, true, false, 1);

	int a = _getch();

	if (a == 224)
		_getch();

	image_layer.eraseImage(&image_layer, false);
	image_layer.eraseImage(&image_layer, true);
}

// 시스템 메시지 (화면 가운데에 뜨는 메시지) 출력
void Game_system_message(const char* str)
{
	int center_x = SCREEN_X * 16 / 2;
	int center_y = SCREEN_Y * 16 / 2;
	//Image im = { "", center_x, center_y, 16, 0, bitmap_system_msg, true };

	//image_layer.appendImage(&image_layer, im, false);

	//image_layer.startRender(&image_layer);
	_renderAndFade_value(&image_layer, NULL, false, 90);

	printText(image_layer._consoleDC, 0, center_y - 30, center_x * 2, center_y + 400, 
		"강원교육튼튼", 54, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK, str);

	sleep_(1500);

	//image_layer.endRender(&image_layer);
	_renderAndFade_value(&image_layer, NULL, true, 90);

	image_layer.renderAll(&image_layer);
}

// 엔딩크레딧 출력!
void Game_ending_credit(const char* str)
{
	Music_stop_background();

	image_layer.fadeOut(&image_layer, NULL);
	image_layer.clearImage(&image_layer, false);

	Music_set_background(MAKEINTRESOURCE(IDR_WAVE_ENDING));

	int center_x = SCREEN_X * 16 / 2;

	int lines = 1;
	for (int i = 0; str[i] != 0; i++)
	{
		if (str[i] == '\n')
			lines++;
	}

	for (int i = 0; i < SCREEN_Y * 16 + 58 * lines; i += 1)
	{
		image_layer.startRender(&image_layer);

		printText(image_layer.bufferDC, 10, SCREEN_Y*16 + 50 - i, SCREEN_X * 16 - 10, SCREEN_Y*16 - i + 58 * lines,
			"강원교육튼튼", 54, RGB(255, 255, 255), DT_CENTER | DT_WORDBREAK, str);

		image_layer.endRender(&image_layer);
		sleep_(20);
	}
	
	Music_stop_background("ending.wav");
}

int map_x = 0, map_y = 0; // 현재 화면에 보이는 맵의 시작 x, y좌표
int player_x = 10, player_y = 10; // 현재 플레이어의 x, y좌표

bool is_died = 0; // 플레이어가 죽었는지 여부 (Game_die() 로 인해 죽었으면 Game_modal()의 메인 loop에서 이걸 다시 0으로 만들고 게임을 초기화하고 끝낸다)

// 이거는 스택처럼 사용됨
int last_x_arr[100];
int last_y_arr[100];
int last_scene[100]; // 여기에 SCENE_XXX define 들이 사용됨!

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

int** map_; // 현재 맵
int max_x, max_y; // 현재 맵의 크기

int current_scene_id; // 현재 보이는 장면의 id (이거도 SCENE_XXX define 들이 사용된다!)

bool fixed_map; // 맵의 시점 고정 여부! 이게 true이면 사람이 맵 경계쪽으로 움직여도 시점이 바뀌지 않는다

// 현재 맵의 구조물 관련된 정보!
Structure* structure;
int structure_cnt;

// 플레이어가 맵경계를 넘어가거나 맵경계쪽으로 가거나 할때 플레이어 위치나 시점 위치를 수정한다!
void Game_modify_player_pos()
{
	if (player_x < 0)
		player_x = 0;
	if (player_x >= max_x)
		player_x = max_x;
	if (player_y < 0)
		player_y = 0;
	if (player_y >= max_y)
		player_y = max_y;

	if (fixed_map)
		return;

	map_x = next_start_pos(map_x, player_x, SCREEN_X / 8-1, max_x);
	map_y = next_start_pos(map_y, player_y, SCREEN_Y / 8-1, max_y);
}

// 화면에 맵을 출력한다
// fade_in: 맵을 페이드인 하며 출력할지 여부
// x_offset, y_offset: 화면 좌표상에서 이 전체 이미지의 offset 크기 (지진 출력 시에 사용된다)
void Game_print_map_impl(bool fade_in, int x_offset, int y_offset)
{
	image_layer.imageCount = 0;

	Image a = { "", 0, 0, 0, 0, bitmap_tile[0] };

	for (int y = -1; y < SCREEN_Y / 8 + 1; y++)
	{
		for (int x = -1; x < SCREEN_X / 8 + 1; x++)
		{
			int ax = map_x + x;
			int ay = map_y + y;

			/*if (map_[ay][ax] == 0)
			{
				a.x = x * 16 * 8;
				a.y = y * 16 * 8;
				image_layer.appendImage(&image_layer, a, false);
			}*/

			if (ax < 0 || ay < 0)
				continue;

			if (map_[ay][ax] == -1)
				continue;

			a.x = x * 16 * 8 + x_offset;
			a.y = y * 16 * 8 + y_offset;
			a.bitmap = bitmap_tile[map_[ay][ax]];

			if (map_[ay][ax] == 0)
				a.scale = 2;
			else
				a.scale = 0;

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
		a.x = (structure[i].x - map_x) * 16 * 8 + x_offset;
		a.y = (structure[i].y - map_y) * 16 * 8 + y_offset;

		a.scale = structure[i].scale;

		image_layer.appendImage(&image_layer, a, false);
	}

	a.bitmap = bitmap_player[player_idx];
	a.x = (player_x - map_x) * 16 * 8 + 16 * 4 + x_offset;
	a.y = (player_y - map_y) * 16 * 8 + 16 * 4 + y_offset;
	a.scale = .7;

	a.isCenter = true;

	image_layer.appendImage(&image_layer, a, false);

	if (fade_in)
		image_layer.fadeIn(&image_layer, NULL);
	else
		image_layer.renderAll(&image_layer);
}

// 화면에 맵을 출력한다
// fade_in : 페이드 인 여부
void Game_print_map(bool fade_in)
{
	Game_print_map_impl(fade_in, 0, 0);

	//TRACE("image_layer size: %d\n", image_layer.imageCount);
}

// 화면에 맵을 지진 효과를 내서 출력한다
// ms: 몇 밀리초동안 지진 효과를 낼지
void Game_print_earthquake(int ms)
{
	for (int i = 0; i < ms; i += 25)
	{
		int ax = rand() % 21 - 10;
		int ay = rand() % 21 - 10;

		Game_print_map_impl(false, ax, ay);

		sleep_(25);
	}

	Game_print_map_impl(false, 0, 0);
}

// 건물에 막혀서 앞으로 갈수 없는 지 판단하는 함수
// 만약 막혀서 앞으로 못 간다면 어디에 막혔는지 반환한다!
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

// 선택 창을 띄운다
// 기본값으로 플레이어 오른쪽 아래에 선택창이 뜬다!
// 근데 지금 이 코드를 쓰는 곳은 없는것같다..
// 이 함수와 이 아래의 select_box 뜨는 모든 함수들은 str가 선택지 배열, cnt가 선택지 개수이다
// 반환값은 뭐가 선택됐는지 0부터 cnt-1까지 중에 반환된다 (Game_modal_select_box 한정 esc를 누르면 -1이 반환된다)
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
				"강원교육튼튼", 40, color, DT_CENTER, str[i]);
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

// 말풍선 + 선택창을 띄운다!
// bubble_type에 따라 말풍선이 결정된다 (0: 김산천, 1: 동현이, 2: ziaoming)
int Game_modal_select_box_speech_person(char* speech, char(*str)[100], int cnt, int bubble_type)
{
	bool is_wide = (bubble_type == 2);

	Game_speech_nowait(speech, false, is_wide, bubble_type);

	int last_image_cnt = image_layer.imageCount;

	int now = 0;

	int width = 0;
	for (int i = 0; i < cnt; i++)
	{
		int sz = getTextWidth(image_layer.bufferDC, "강원교육튼튼", 40, str[i]);

		if (width < sz)
			width = sz;
	}

	void (*print_text)(HDC, int, int, int, int, char*, int, COLORREF, int, const char*) = printText;

	if (is_wide)
		print_text = printTextW;

	while (true)
	{
		image_layer.startRender(&image_layer);

		print_text(image_layer.bufferDC, 100, 70 * 16 + 20, 180 * 16 - 85, 96 * 16 - 20, "강원교육튼튼", 54, RGB(0, 0, 0), DT_LEFT | DT_WORDBREAK, speech);

		for (int k = 0; k < cnt; k++)
		{
			int i = cnt - k - 1;

			COLORREF color = RGB(0, 0, 0);
			if (k == now)
				color = RGB(255, 0, 0);

			printText(image_layer.bufferDC, 168 * 16 - 10 - width, 86 * 16 - 10 - 0 * cnt - 92 * i,
				170 * 16 + (335 % 300), 90 * 16 - 10 - 0 * cnt + 100 * i + 60,
				"강원교육튼튼", 63, color, DT_RIGHT, str[k]);
		}

		image_layer.endRender(&image_layer);

		int ch = _getch();

		if (ch == UP && now > 0)
			now--;
		else if (ch == DOWN && now < cnt - 1)
			now++;
		else if (ch == VK_SPACE || ch == VK_RETURN)
		{
			image_layer.eraseImage(&image_layer, true);
			return now;
		}
	}
}

// 위의 일반화된 함수
// 무조건 김산천 말풍선을 띄운다
int Game_modal_select_box_speech(char* speech, char(*str)[100], int cnt)
{
	return Game_modal_select_box_speech_person(speech, str, cnt, 0);
}

// 이 함수 포인터들은 모두 Scene 객체를 읽어와서 만들어진다
// Game_modal, Game_change_scene 에서 아마 객체를 읽는다!

void (*Game_on_structure_active)(int st, int dir); // 구조물이 활성화됐을때 (플레이어가 구조물에 다가갔을때), 기본값으로 호출되는 함수 (Structure::on_active가 NULL이면 기본값으로 이 함수가 호출된다)
void (*Game_on_start)(); // 새 장면이 시작됐을 때 호출되는 함수!
void (*Game_on_key_pressed)(char ch); // 무언가 내부 시스템 키 (방향키, esc) 가 아닌 것이 입력됐을때 호출되는 함수!
void (*Game_on_tick)(); // 매 50ms마다 호출되는 함수! (말풍선 등으로 스레드를 잡고있으면 그럴때에는 호출되지 않고 대기하다가 나중에 호출된다)

// 현재 장면을 바꾸는 함수
// sc : 바꿀 장면을 나타내는 객체
// is_enter : 어떤 공간으로 들어가는지 여부 (true면 들어가고 false면 나간다)
// 들어가는지/나가는지 차이는 스택에 쌓이는지 안쌓이는지 여부가 가장 크다
void Game_change_scene(Scene sc, bool is_enter)
{
	image_layer.fadeOut(&image_layer, NULL);

	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	Game_on_structure_active = sc.on_structure_active;
	Game_on_start = sc.on_start;
	Game_on_key_pressed = sc.on_key_pressed;

	fixed_map = sc.fixed_map;

	Game_on_tick = sc.on_tick;

	player_idx = 0;

	if (is_enter)
	{
		last_x_arr[last_arr_sz] = player_x;
		last_y_arr[last_arr_sz] = player_y;
		last_scene[last_arr_sz] = current_scene_id;
		last_arr_sz++;

		player_x = sc.start_x; player_y = sc.start_y;
		current_scene_id = sc.scene_id;
		map_x = 0; map_y = 0;

		Game_modify_player_pos();

		Game_return_val = -1;
	}
	else
	{
		player_x = last_x_arr[last_arr_sz - 1];
		player_y = last_y_arr[last_arr_sz - 1];
		current_scene_id = last_scene[last_arr_sz - 1];
		last_arr_sz--;

		Game_modify_player_pos();
	}

	sleep_(1000);

	Game_print_map(true);

	Game_on_start();

	if (Game_return_val != -1 && sc.on_return != NULL)
		sc.on_return(Game_return_val);
}

// 죽을때 호출되는 함수!
void Game_die()
{
	Music_stop_background();

	image_layer.fadeOut(&image_layer, NULL);

	sleep_(1000);

	image_layer.clearImage(&image_layer, false);

	Image im = { "", 0, 0, 2, 0, bitmap_youdie };
	image_layer.appendImage(&image_layer, im, false);

	image_layer.fadeIn(&image_layer, NULL);

	Music_play(MAKEINTRESOURCE(IDR_WAVE_YOUDIE));

	sleep_(2000);

	image_layer.fadeOut(&image_layer, NULL);

	image_layer.clearImage(&image_layer, false);

	sleep_(1000);

	Game_return_val = -1;

	SceneDimigo_reset();
	SceneCafeteria_reset();

	is_died = true;
}

// 클리어했을때 호출되는 함수!
// 사실 엔딩크레딧이랑 이 함수는 별개다 둘이 따로따로 호출해줘야 한다!
void Game_clear()
{
	image_layer.fadeOut(&image_layer, NULL);

	sleep_(1000);

	image_layer.clearImage(&image_layer, false);

	Image im = { "", 0, 0, 2, 0, bitmap_clear };
	image_layer.appendImage(&image_layer, im, false);

	image_layer.fadeIn(&image_layer, NULL);

	sleep_(2000);

	image_layer.fadeOut(&image_layer, NULL);

	image_layer.clearImage(&image_layer, false);

	sleep_(1000);
}

// 전체 게임 시스템을 리셋하는 함수!
void Game_reset_all()
{
	Game_return_val = -1;

	SceneDimigo_reset();
	SceneCafeteria_reset();
	SceneBongwan_reset();
	SceneHealthjang_reset();

	is_died = true;
}

// 장면을 나올때 반환값을 지정하는 함수!
// 이 함수가 호출되면 반환값을 가지고 있다가 장면을 나갈 때 Scene::on_return()의 인자로 넘어간다!
void Game_set_return(int ret)
{
	Game_return_val = ret;
}

// 파일 저장 창을 띄우는 함수!
// 기본적으로 esc를 눌렀을때 호출되고, 반환값은 뭔가 하려고 했는데 쓸데없는 것 같다..
int Game_select_save_file()
{
	Image im1 = { "", 0, 0, 2, 0, bitmap_loading_none };
	Image im2 = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 / 2, 2, 0, bitmap_save, true };

	image_layer.appendImage(&image_layer, im1, false);
	image_layer.appendImage(&image_layer, im2, false);

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
			sprintf(buf, "슬롯 %d", k+1);

			if(cursor == k)
				printText(image_layer.bufferDC, start_x + 600*i, 1150, start_x + 600 + 600*i, 1150 + 75, "강원교육튼튼", 80, RGB(255, 0, 0), DT_CENTER, buf);
			else
				printText(image_layer.bufferDC, start_x + 600*i, 1150, start_x + 600 + 600*i, 1150 + 75, "강원교육튼튼", 80, RGB(255, 255, 255), DT_CENTER, buf);
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
			Game_save(cursor);
			break;
		}
	}

	image_layer.eraseImage(&image_layer, false);
	image_layer.eraseImage(&image_layer, true);

	return 1;
}

// 게임을 slot 번째 슬롯에 저장한다!
void Game_save(int slot)
{
	SaveFile* sf = SaveFile_new(200);

	SaveFile_append(sf, player_x);
	SaveFile_append(sf, player_y);
	SaveFile_append(sf, player_idx);

	SaveFile_append(sf, current_scene_id);
	SaveFile_append(sf, Game_return_val);

	SaveFile_append(sf, last_arr_sz);

	for (int i = 0; i < last_arr_sz; i++)
	{
		SaveFile_append(sf, last_x_arr[i]);
		SaveFile_append(sf, last_y_arr[i]);
		SaveFile_append(sf, last_scene[i]);
	}

	SaveFile_append(sf, quest_progress_cafeteria);
	SaveFile_append(sf, quest_progress_bongwan);
	SaveFile_append(sf, quest_progress_misemonji);

	SceneDimigo_save(sf);

	char filename[MAX_PATH];
	sprintf(filename, "%s\\save%d.data", save_path, slot + 1);

	SaveFile_write(sf, filename);

	SaveFile_free(sf);

	char buf[110];
	sprintf(buf, "슬롯 %d에 저장되었습니다!", slot+1);
	Game_system_message(buf);
}

// 게임 창을 만든다!
// 코드 구조가 수정되면서 이거만 호출해서 새 창을 만들수 없게 되었다!
// 이 함수 대신 Game_modal_new() 또는 Game_modal_load()를 사용해야 한다
void Game_modal()
{
	sleep_(500);

	Image a = { "", 0, 0, 2, 0, bitmap_loading_none };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.fadeIn(&image_layer, NULL);

	sleep_(1000);

	game_image[0].bitmap = bitmap_loading_image;

	image_layer.renderAll(&image_layer);

	sleep_(2000);

	image_layer.fadeOut(&image_layer, NULL);
	image_layer.clearImage(&image_layer, false);

	sleep_(1000);

	map_x = 0; map_y = 0;
	Game_modify_player_pos();

	Game_print_map(true);

	Music_set_background(MAKEINTRESOURCE(IDR_WAVE_MAINBGM));

	Game_on_start();

	clock_t last = clock();
	for (;;)
	{
		if (_kbhit())
		{
			int ch = _getch();
			int last_x = player_x, last_y = player_y;

			if (ch == UP)
			{
				player_y--;
				player_idx = 0;
			}
			else if (ch == DOWN)
			{
				player_y++;
				player_idx = 1;
			}
			else if (ch == LEFT)
			{
				player_x--;
				player_idx = 2;
			}
			else if (ch == RIGHT)
			{
				player_x++;
				player_idx = 3;
			}
			else if (ch == VK_ESCAPE)
			{
				//Game_speechbubble("왠지 저장 버튼이 뜰 것 같다!");
				Game_select_save_file();
			}
			else if(ch != 224)
			{
				if (Game_on_key_pressed != NULL)
					Game_on_key_pressed(ch);
			}

			int check_st = 0;
			if ((check_st = Game_check_block()) != -1)
			{
				player_x = last_x;
				player_y = last_y;

				Game_modify_player_pos();
				Game_print_map(false);

				if (structure[check_st].on_active != NULL)
					structure[check_st].on_active(check_st, ch);
				else
					Game_on_structure_active(check_st, ch);
			}

			if (is_died)
			{
				is_died = false;
				break;
			}

			Game_modify_player_pos();
			Game_print_map(false);
		}

		if (is_died)
		{
			is_died = false;
			break;
		}

		clock_t now = clock();

		if (now - last >= 50)
		{
			if(Game_on_tick != NULL)
				Game_on_tick();

			last = now;
		}

		//sleep_(50);
	}
}

// 새 게임을 만든다!
void Game_modal_new()
{
	Scene sc = SceneDimigo_load();

	current_scene_id = sc.scene_id;

	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	player_x = sc.start_x;
	player_y = sc.start_y;

	Game_on_structure_active = sc.on_structure_active;
	Game_on_start = sc.on_start;

	fixed_map = sc.fixed_map;

	Game_on_key_pressed = sc.on_key_pressed;

	Game_on_tick = sc.on_tick;

	player_idx = 0;

	Game_modal();
}

// 파일에서 게임을 불러온다!
bool Game_modal_load(int slot)
{
	char filename[MAX_PATH];
	sprintf(filename, "%s\\save%d.data", save_path, slot + 1);

	SaveFile* sf = SaveFile_load(filename);

	if (sf == NULL)
		return false;

	image_layer.fadeOut(&image_layer, NULL);
	Music_stop_background();

	player_x = SaveFile_read(sf);
	player_y = SaveFile_read(sf);
	player_idx = SaveFile_read(sf);

	current_scene_id = SaveFile_read(sf);
	Game_return_val = SaveFile_read(sf);

	last_arr_sz = SaveFile_read(sf);

	for (int i = 0; i < last_arr_sz; i++)
	{
		last_x_arr[i] = SaveFile_read(sf);
		last_y_arr[i] = SaveFile_read(sf);
		last_scene[i] = SaveFile_read(sf);
	}

	quest_progress_cafeteria = SaveFile_read(sf);
	quest_progress_bongwan = SaveFile_read(sf);
	quest_progress_misemonji = SaveFile_read(sf);

	SceneDimigo_load_file(sf);

	SaveFile_free(sf);

	Scene sc = scene_load_function[current_scene_id]();
	map_ = sc.load_map(&max_x, &max_y);
	structure = sc.load_structure(&structure_cnt);

	Game_on_structure_active = sc.on_structure_active;
	Game_on_start = sc.on_start;

	fixed_map = sc.fixed_map;

	Game_on_key_pressed = sc.on_key_pressed;

	Game_on_tick = sc.on_tick;

	Game_modal();

	return true;
}