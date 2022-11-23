#include "SceneSingwan.h"
#include "Game.h"

#include "SceneDimigo.h"
#include "SceneBiggangdang.h"

int scene_singwan_map[100][100] = { 0, };
int scene_singwan_x = 100, scene_singwan_y = 20;
int quest_progress_singwan = 0;

Structure scene_singwan_structure[100];
int scene_singwan_struct_cnt = 0;

bool struct_loaded_singwan = 0;

Scene SceneSingwan_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneSingwan_load_map;
	scene.load_structure = SceneSingwan_load_structure;
	scene.on_structure_active = SceneSingwan_on_structure_active;
	scene.on_start = SceneSingwan_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** singwan_map_return = NULL;

int** SceneSingwan_load_map(int* x, int* y)
{
	*x = scene_singwan_x; *y = scene_singwan_y;

	if (singwan_map_return != NULL)
		return singwan_map_return;

	int** res = malloc(sizeof(int*) * (scene_singwan_y + 10));

	for (int i = 0; i < scene_singwan_y + 10; i++)
	{
		res[i] = scene_singwan_map[i];
		memset(scene_singwan_map[i], -1, sizeof(int) * scene_singwan_x);
	}

	return singwan_map_return = res;
}

Structure* SceneSingwan_load_structure(int* sz)
{
	Structure* structure = scene_singwan_structure;

	Structure st[5] = {
		{2, -5, 0, 0, bitmap_singwan_inside, false, true, NULL, 1.6},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneSingwan_on_rice*/, 1.6},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneSingwan_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneSingwan_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 0, 9, 10, NULL, false, false, SceneSingwan_on_biggangdang},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_singwan_struct_cnt = 5;
	*sz = scene_singwan_struct_cnt;

	if (struct_loaded_singwan)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_singwan = true;
	return structure;
}

void SceneSingwan_on_start()
{

}

void SceneSingwan_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
	{
		Game_change_scene(SceneDimigo_load(), false);
	}
}

void SceneSingwan_on_biggangdang(int st, int dir)
{
	char str[2][100] = {
		"들어가보자!",
		"돌아가자."
	};

	if (Game_modal_select_box_speech("강당에 들어갈까?", str, 2) == 0)
	{
		Game_change_scene(SceneBiggangdang_load(), true);
	}
}

void SceneSingwan_on_structure_active(int st, int dir)
{
}

void SceneSingwan_reset()
{
	struct_loaded_singwan = false;
}
