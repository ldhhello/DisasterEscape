#include "SceneHakbonggwan.h"
#include "Game.h"

#include "SceneDimigo.h"

int scene_hakbonggwan_map[100][100] = { 0, };
int scene_hakbonggwan_x = 100, scene_hakbonggwan_y = 20;
int quest_progress_hakbonggwan = 0;

Structure scene_hakbonggwan_structure[100];
int scene_hakbonggwan_struct_cnt = 0;

bool struct_loaded_hakbonggwan = 0;

Scene SceneHakbonggwan_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.scene_id = SCENE_HAKBONGGWAN;

	scene.load_map = SceneHakbonggwan_load_map;
	scene.load_structure = SceneHakbonggwan_load_structure;
	scene.on_structure_active = SceneHakbonggwan_on_structure_active;
	scene.on_start = SceneHakbonggwan_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	scene.background_music = MAKEINTRESOURCE(IDR_WAVE_HAKBONGGWAN);

	return scene;
}

int** hakbonggwan_map_return = NULL;

int** SceneHakbonggwan_load_map(int* x, int* y)
{
	*x = scene_hakbonggwan_x; *y = scene_hakbonggwan_y;

	if (hakbonggwan_map_return != NULL)
		return hakbonggwan_map_return;

	int** res = malloc(sizeof(int*) * (scene_hakbonggwan_y + 10));

	for (int i = 0; i < scene_hakbonggwan_y + 10; i++)
	{
		res[i] = scene_hakbonggwan_map[i];
		memset(scene_hakbonggwan_map[i], -1, sizeof(int) * scene_hakbonggwan_x);
	}

	return hakbonggwan_map_return = res;
}

Structure* SceneHakbonggwan_load_structure(int* sz)
{
	Structure* structure = scene_hakbonggwan_structure;

	Structure st[5] = {
		{2, -5, 0, 0, bitmap_hakbonggwan_inside, false, true, NULL, 1.6},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneHakbonggwan_on_rice*/, 1.6},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneHakbonggwan_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneHakbonggwan_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_hakbonggwan_struct_cnt = 5;
	*sz = scene_hakbonggwan_struct_cnt;

	if (struct_loaded_hakbonggwan)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_hakbonggwan = true;
	return structure;
}

void SceneHakbonggwan_on_start()
{
	outside_time += 10000;
}

void SceneHakbonggwan_on_door(int st, int dir)
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

void SceneHakbonggwan_on_structure_active(int st, int dir)
{
}

void SceneHakbonggwan_reset()
{
	struct_loaded_hakbonggwan = false;
}
