#include "SceneHealthjang.h"
#include "Game.h"

#include "SceneDimigo.h"
#include "SceneGangdang.h"

int scene_healthjang_map[100][100] = { 0, };
int scene_healthjang_x = 100, scene_healthjang_y = 20;
int quest_progress_healthjang = 0;

Structure scene_healthjang_structure[100];
int scene_healthjang_struct_cnt = 0;

bool struct_loaded_healthjang = 0;

Scene SceneHealthjang_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneHealthjang_load_map;
	scene.load_structure = SceneHealthjang_load_structure;
	scene.on_structure_active = SceneHealthjang_on_structure_active;
	scene.on_start = SceneHealthjang_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** healthjang_map_return = NULL;

int** SceneHealthjang_load_map(int* x, int* y)
{
	*x = scene_healthjang_x; *y = scene_healthjang_y;

	if (healthjang_map_return != NULL)
		return healthjang_map_return;

	int** res = malloc(sizeof(int*) * (scene_healthjang_y + 10));

	for (int i = 0; i < scene_healthjang_y + 10; i++)
	{
		res[i] = scene_healthjang_map[i];
		memset(scene_healthjang_map[i], -1, sizeof(int) * scene_healthjang_x);
	}

	return healthjang_map_return = res;
}

Structure* SceneHealthjang_load_structure(int* sz)
{
	Structure* structure = scene_healthjang_structure;

	Structure st[5] = {
		{2, -5, 0, 0, bitmap_healthjang, false, true, NULL, 1.6},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneHealthjang_on_rice*/, 1.6},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneHealthjang_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneHealthjang_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_healthjang_struct_cnt = 5;
	*sz = scene_healthjang_struct_cnt;

	if (struct_loaded_healthjang)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_healthjang = true;
	return structure;
}

void SceneHealthjang_on_start()
{

}

void SceneHealthjang_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
	{
		Game_change_scene(SceneGangdang_load(), false);
	}
}

void SceneHealthjang_on_structure_active(int st, int dir)
{
}

void SceneHealthjang_reset()
{
	struct_loaded_healthjang = false;
}
