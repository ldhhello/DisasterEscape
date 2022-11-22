#include "SceneBongwan.h"
#include "Game.h"

#include "SceneDimigo.h"

int scene_bongwan_map[100][100] = { 0, };
int scene_bongwan_x = 100, scene_bongwan_y = 20;
int quest_progress_bongwan = 0;

Structure scene_bongwan_structure[100];
int scene_bongwan_struct_cnt = 0;

bool struct_loaded_bongwan = 0;

Scene SceneBongwan_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneBongwan_load_map;
	scene.load_structure = SceneBongwan_load_structure;
	scene.on_structure_active = SceneBongwan_on_structure_active;
	scene.on_start = SceneBongwan_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** bongwan_map_return = NULL;

int** SceneBongwan_load_map(int* x, int* y)
{
	*x = scene_bongwan_x; *y = scene_bongwan_y;

	if (bongwan_map_return != NULL)
		return bongwan_map_return;

	int** res = malloc(sizeof(int*) * (scene_bongwan_y + 10));

	for (int i = 0; i < scene_bongwan_y + 10; i++)
	{
		res[i] = scene_bongwan_map[i];
		memset(scene_bongwan_map[i], -1, sizeof(int) * scene_bongwan_x);
	}

	return bongwan_map_return = res;
}

Structure* SceneBongwan_load_structure(int* sz)
{
	Structure* structure = scene_bongwan_structure;

	Structure st[8] = {
		{2, -2, 0, 0, bitmap_bongwan_inside, false, true, NULL, 1.2},
		{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*Scenebongwan_on_rice*/, 1.6},
		{10, 10, 1, 1, bitmap_towel, false, false, Scenebongwan_on_clean_air, 2},
		{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*Scenebongwan_on_water*/, 2},

		{0, 12, 21, 1, NULL, false, false, SceneBongwan_on_door},
		//{15, 7, 4, 8, bitmap_house, false, true},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_bongwan_struct_cnt = 8;
	*sz = scene_bongwan_struct_cnt;

	if (struct_loaded_bongwan)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_bongwan = true;
	return structure;
}

void SceneBongwan_on_start()
{
	if (quest_progress_bongwan == 1)
	{
		Game_speechbubble("본관에 왔더니 배고파!");
		Game_speechbubble("저기 밥이 보이는데, 먹어보자!");
		quest_progress_bongwan = 2;
	}
}

void Scenebongwan_on_clean_air(int st, int dir)
{
	if (quest_progress_bongwan == 2)
	{
		Game_speechbubble("환기 시스템이 가동되지 않았다!");
		Game_die();
		return;
	}
}

void SceneBongwan_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
		Game_change_scene(SceneDimigo_load(), false);
}

void SceneBongwan_on_structure_active(int st, int dir)
{
	if (dir != UP)
		return;

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
		Game_die();
		break;
	case 2:
		//Game_speechbubble("집을 잡아먹는다고??? 난 못 먹어..");
		scene_bongwan_structure[st].is_hide = true;

		Sleep(100);
		Game_print_map(false);
		Sleep(500);

		Game_speechbubble("집을 잡아먹었다!!");

		break;
	case 3:
		Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
		break;
	}
}
