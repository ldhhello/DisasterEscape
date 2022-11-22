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

	scene.load_map = SceneHakbonggwan_load_map;
	scene.load_structure = SceneHakbonggwan_load_structure;
	scene.on_structure_active = SceneHakbonggwan_on_structure_active;
	scene.on_start = SceneHakbonggwan_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** Hakbonggwan_map_return = NULL;

int** SceneHakbonggwan_load_map(int* x, int* y)
{
	*x = scene_Hakbonggwan_x; *y = scene_Hakbonggwan_y;

	if (Hakbonggwan_map_return != NULL)
		return Hakbonggwan_map_return;

	int** res = malloc(sizeof(int*) * (scene_Hakbonggwan_y + 10));

	for (int i = 0; i < scene_Hakbonggwan_y + 10; i++)
	{
		res[i] = scene_Hakbonggwan_map[i];
		memset(scene_Hakbonggwan_map[i], -1, sizeof(int) * scene_Hakbonggwan_x);
	}

	return Hakbonggwan_map_return = res;
}

Structure* SceneHakbonggwan_load_structure(int* sz)
{
	Structure* structure = scene_Hakbonggwan_structure;

	Structure st[10] = {
		{2, -2, 0, 0, bitmap_Hakbonggwan_inside, false, true, NULL, 1.2},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneHakbonggwan_on_rice*/, 1.6},
		{10, 10, 1, 2, bitmap_puricare, false, false, SceneHakbonggwan_on_clean_air, 0.25},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneHakbonggwan_on_water*/, 2},
		{2, 5, 10, 2, NULL, false, false, SceneHakbonggwan_on_table},
		{0, 12, 21, 1, NULL, false, false, SceneHakbonggwan_on_door},
		{15, 0, 6, 5, NULL, false, false, SceneHakbonggwan_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_Hakbonggwan_struct_cnt = 10;
	*sz = scene_Hakbonggwan_struct_cnt;

	if (struct_loaded_Hakbonggwan)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_Hakbonggwan = true;
	return structure;
}

void SceneHakbonggwan_on_start()
{
	if (quest_progress_Hakbonggwan == 1)
	{
		Game_speechbubble("휴, 이제야 마음이 놓이네!");
		Game_speechbubble("공기 청정기를 켜서 공기를 정화시켜 보자.");
		quest_progress_Hakbonggwan = 2;
	}
}//