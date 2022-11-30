#include "SceneBiggangdang.h"
#include "Game.h"

#include "SceneDimigo.h"
#include "SceneSingwan.h"

#include "ChineseConstant.h"

int scene_biggangdang_map[100][100] = { 0, };
int scene_biggangdang_x = 100, scene_biggangdang_y = 20;
int quest_progress_biggangdang = 0;

Structure scene_biggangdang_structure[100];
int scene_biggangdang_struct_cnt = 0;

bool struct_loaded_biggangdang = 0;

Scene SceneBiggangdang_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.scene_id = SCENE_BIGGANGDANG;

	scene.load_map = SceneBiggangdang_load_map;
	scene.load_structure = SceneBiggangdang_load_structure;
	scene.on_structure_active = SceneBiggangdang_on_structure_active;
	scene.on_start = SceneBiggangdang_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** biggangdang_map_return = NULL;

int** SceneBiggangdang_load_map(int* x, int* y)
{
	*x = scene_biggangdang_x; *y = scene_biggangdang_y;

	if (biggangdang_map_return != NULL)
		return biggangdang_map_return;

	int** res = malloc(sizeof(int*) * (scene_biggangdang_y + 10));

	for (int i = 0; i < scene_biggangdang_y + 10; i++)
	{
		res[i] = scene_biggangdang_map[i];
		memset(scene_biggangdang_map[i], -1, sizeof(int) * scene_biggangdang_x);
	}

	return biggangdang_map_return = res;
}

Structure* SceneBiggangdang_load_structure(int* sz)
{
	Structure* structure = scene_biggangdang_structure;

	Structure st[6] = {
		{2, -1, 0, 0, bitmap_biggangdang, false, true, NULL, 1.22},
		{7, 11, 1, 1, bitmap_ziaoming, false, false, SceneBiggangdang_on_ziaoming, 0.16},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneBiggangdang_on_rice*/, 1.6},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneBiggangdang_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneBiggangdang_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_biggangdang_struct_cnt = 6;
	*sz = scene_biggangdang_struct_cnt;

	if (struct_loaded_biggangdang)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_biggangdang = true;
	return structure;
}

void SceneBiggangdang_on_start()
{
	outside_time += 5000;
}

void SceneBiggangdang_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
	{
		Game_change_scene(SceneSingwan_load(), false);
	}
}

void SceneBiggangdang_on_ziaoming(int st, int dir)
{
	Game_speechbubble_ziaoming(constant_i_am_chinese);
	Game_speechbubble_ziaoming(constant_im_from_beijing);

	char oong[2][100] = {
		"Hola!",
		"先是一然后"
	};

	if (Game_modal_select_box_speech_person(constant_do_you_love_beijing_tienanmen, oong, 2, 2) >= 0)
	{
		Game_system_message("Красный Лоро Булгагоги!");
		Game_die();
		return;
	}
}

void SceneBiggangdang_on_structure_active(int st, int dir)
{
}

void SceneBiggangdang_reset()
{
	struct_loaded_biggangdang = false;
}
