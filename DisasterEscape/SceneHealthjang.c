#include "SceneHealthjang.h"
#include "Game.h"

#include "SceneDimigo.h"
#include "SceneGangdang.h"
#include "SceneBongwan.h"

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

	scene.scene_id = SCENE_HEALTHJANG;

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

	Structure st[7] = {
		{2, -5, 0, 0, bitmap_healthjang, false, true, NULL, 1.6},
		{5, 4, 1, 2, bitmap_kf94, false, false, SceneHealthjang_on_kf94, 0.5},
		{15, 6, 2, 6, bitmap_donghyun, false, false, SceneHealthjang_on_donghyun, 0.25},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*SceneHealthjang_on_rice*/, 1.6},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*SceneHealthjang_on_water*/, 2},
		{0, 12, 21, 1, NULL, false, false, SceneHealthjang_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_healthjang_struct_cnt = 7;
	*sz = scene_healthjang_struct_cnt;

	if (struct_loaded_healthjang)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_healthjang = true;
	return structure;
}

void SceneHealthjang_on_start()
{
	if (quest_progress_misemonji >= 10)
	{
		scene_healthjang_structure[1].is_hide = true;
		Game_print_map(false);
	}
	else
		scene_healthjang_structure[1].is_hide = false;

	outside_time += 5000;
}

void SceneHealthjang_on_door(int st, int dir)
{
	char str[2][100] = {
		"������",
		"�ӹ�����"
	};

	if (Game_modal_select_box_speech("������ ��������?", str, 2) == 0)
	{
		Game_change_scene(SceneGangdang_load(), false);
	}
}

void SceneHealthjang_on_kf94(int st, int dir)
{
	if (quest_progress_misemonji != 2)
	{
		Game_speechbubble("����ũ�� ���� �� ����?");
		return;
	}

	Game_speechbubble("����ũ�� ã�Ҿ�!");
	Game_system_message("�������� ����.");
	scene_healthjang_structure[1].is_hide = true;
	quest_progress_misemonji = 10;
}

void SceneHealthjang_on_donghyun(int st, int dir)
{
	if (quest_progress_misemonji < 10)
	{
		Game_speechbubble_ldh("�� ����ũ ��� ����..?�Ф�");
	}
	else
	{
		char oong[2][100] = {
			"�̾�.. ���� ���ƾ�Ф�",
			"���Ҹ��� ���� �װ� �� ����!!"
		};

		if (Game_modal_select_box_speech_person("Ȥ�� �װ� �� ����ũ ���İ���?", oong, 2, 1) == 0)
		{
			Game_speechbubble_ldh("�� �׷��� �� �ôµ�..");
			Game_die();
		}
		else
		{
			Game_speechbubble_ldh("������ ���� ��, ���� �� �þ�.");
			Game_die();
		}
	}
}

void SceneHealthjang_on_structure_active(int st, int dir)
{
}

void SceneHealthjang_reset()
{
	struct_loaded_healthjang = false;
}
