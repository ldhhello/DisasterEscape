#include "SceneGangdang.h"
#include "Game.h"

#include "SceneDimigo.h"
#include "SceneHealthjang.h"

int scene_gangdang_map[100][100] = { 0, };
int scene_gangdang_x = 100, scene_gangdang_y = 20;
int quest_progress_gangdang = 0;

Structure scene_gangdang_structure[100];
int scene_gangdang_struct_cnt = 0;

bool struct_loaded_gangdang = 0;

Scene SceneGangdang_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneGangdang_load_map;
	scene.load_structure = SceneGangdang_load_structure;
	scene.on_structure_active = SceneGangdang_on_structure_active;
	scene.on_start = SceneGangdang_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** gangdang_map_return = NULL;

int** SceneGangdang_load_map(int* x, int* y)
{
	*x = scene_gangdang_x; *y = scene_gangdang_y;

	if (gangdang_map_return != NULL)
		return gangdang_map_return;

	int** res = malloc(sizeof(int*) * (scene_gangdang_y + 10));

	for (int i = 0; i < scene_gangdang_y + 10; i++)
	{
		res[i] = scene_gangdang_map[i];
		memset(scene_gangdang_map[i], -1, sizeof(int) * scene_gangdang_x);
	}

	return gangdang_map_return = res;
}

Structure* SceneGangdang_load_structure(int* sz)
{
	Structure* structure = scene_gangdang_structure;

	Structure st[6] = {
		{2, -5, 0, 0, bitmap_gangdang_inside, false, true, NULL, 1.6},
		{0, 9, 21, 1, NULL, false, false, NULL},
		{4, 10, 1, 2, NULL, false, false, SceneGangdang_on_healthjang},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneGangdang_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneGangdang_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_gangdang_struct_cnt = 6;
	*sz = scene_gangdang_struct_cnt;

	if (struct_loaded_gangdang)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_gangdang = true;
	return structure;
}

void SceneGangdang_on_start()
{

}

void SceneGangdang_on_door(int st, int dir)
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

void SceneGangdang_on_healthjang(int st, int dir)
{
	char str[2][100] = {
		"들어가보자!",
		"돌아가자."
	};

	if (Game_modal_select_box_speech("헬스장에 들어갈까?", str, 2) == 0)
	{
		Game_change_scene(SceneHealthjang_load(), true);
	}
}

void SceneGangdang_on_structure_active(int st, int dir)
{
}

void SceneGangdang_reset()
{
	struct_loaded_gangdang = false;
}
