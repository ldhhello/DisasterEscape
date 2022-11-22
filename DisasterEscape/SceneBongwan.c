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

	Structure st[9] = {
		{2, -2, 0, 0, bitmap_bongwan_inside, false, true, NULL, 1.2},
		//{10, 6, 1, 1, bitmap_bibimbap, false, false, NULL/*Scenebongwan_on_rice*/, 1.6},
		{10, 10, 1, 1, bitmap_towel, false, false, Scenebongwan_on_clean_air, 2},
		//{6, 8, 1, 1, bitmap_naoh, false, false, NULL/*Scenebongwan_on_water*/, 2},
		{2, 5, 10, 2, NULL, false, false, SceneBongwan_on_table},
		{0, 12, 21, 1, NULL, false, false, SceneBongwan_on_door},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_bongwan_struct_cnt = 9;
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
		Game_speechbubble("��, ������ ������ ���̳�!");
		Game_speechbubble("���� û���⸦ �Ѽ� ���⸦ ��ȭ���� ����.");
		quest_progress_bongwan = 2;
	}
}//

void SceneBongwan_on_table(int st, int dir)
{
	if (quest_progress_bongwan == 3)
	{

		Game_print_earthquake(1000);


		char oonng[3][100] = {
			"�� �����! �׳� �پ� ����!",
			"�������� �η��� �ʾ�!!",
			"ħ���ϰ� ������ ���� ������ ��ٸ���."
			//�亯
		};


		if (Game_modal_select_box_speech("å�� ������ ������ ���� ������ ���� ������ ��ٸ���!", oonng, 3) != 2)
		{
			Game_print_earthquake(1000);
			Game_system_message("���� ��Ȳ���� ���Ҹ� �����̴� ����\n\n�ſ� ������ �ൿ�Դϴ�.");
			Game_die();
			return;

		}
		else {
			char ooonng[3][100] = {
			"�������� ��ȭ����!",
			"ȭ��Ƿ� ���� ����!",
			"���Թ� ������ ������ ������!"
			//�亯
			};


			if (Game_modal_select_box_speech("������ ���� �� ����! ���� ��� ����?", ooonng, 3) != 2)
			{
				Game_print_earthquake(1000);
				Game_system_message("������ ���߸� �ִ��� �ż��ϰ� ������ �մϴ�.");
				Game_die();
				return;

			}
			else {
				Game_system_message("�ǹ� ������ �����ϼ���!");
				Game_set_return(RETURNVAL_EARTHQUAKE_MISSION);
				quest_progress_bongwan = 4;
			}
		}
		return;
	}
}

void Scenebongwan_on_clean_air(int st, int dir)
{
	if (quest_progress_bongwan == 2)
	{
		char oong[3][100] = {
		"���� �Ʊ��! ���� ���ʹ� ���зε� �����.",
		"� ���� û���⸦ �� ����!",
		"���� û��? ��? �װ� ����?"
		//�亯
		};
		if (Game_modal_select_box_speech("���� û���⸦ �� ����?", oong, 3) != 1)
		{
			Game_system_message("���� �� ������!");
			Game_die();
			return;

		}
		else {
			Game_speechbubble("������ �� �� ����!");
			Game_system_message("����Ʈ �Ϸ�: �ʰ�� �̼�����");

			Game_print_earthquake(1000);

			Game_speechbubble("���� �ڵ����� �������� �� �ξ��� ��.\n\n�� �̷��� ��鸮��?");

			char oonng[3][100] = {
				"����, ������ ������ ����!",
				"�������� ���߰ھ�!",
				"å�� ������ ������� ����!"
				//�亯
			};


			if (Game_modal_select_box_speech("��, �̰� �޴��� ������ �ƴ� �������ݾ�!", oonng, 3) != 2)
			{
				Game_print_earthquake(1000);
				Game_system_message("���� ��Ȳ���� ���Ҹ� �����̴� ����\n\n�ſ� ������ �ൿ�Դϴ�.");
				Game_die();
				return;

			}
			else {
				Game_system_message("å�� ������ �̵��ϼ���!");
				quest_progress_bongwan = 3;
			}
		}
	}
}

void SceneBongwan_on_door(int st, int dir)
{
	char str[2][100] = {
		"������",
		"�ӹ�����"
	};

	if (Game_modal_select_box_speech("������ ��������?", str, 2) == 0)
	{
		if (quest_progress_bongwan != 0 && quest_progress_bongwan != 4)
		{
			Game_speechbubble("����! �ǹ��� �������� �־�!!");
			Game_print_earthquake(1000);

			Game_die();
			return;
		}

		Game_change_scene(SceneDimigo_load(), false);
	}
}

void SceneBongwan_on_structure_active(int st, int dir)
{
	if (dir != UP)
		return;

	char str[4][100] = {
					"����",
					"��������",
					"��ƸԱ�",
					"����ϱ�"
	};

	switch (Game_modal_select_box_speech("���̴�! ����?", str, 4))
	{
	case 0:
		Game_speechbubble("���µ� �����ߴ�!");
		break;
	case 1:
		Game_speechbubble("�������µ� �����ߴ�!");
		Game_die();
		break;
	case 2:
		//Game_speechbubble("���� ��ƸԴ´ٰ�??? �� �� �Ծ�..");
		scene_bongwan_structure[st].is_hide = true;

		Sleep(100);
		Game_print_map(false);
		Sleep(500);

		Game_speechbubble("���� ��ƸԾ���!!");

		break;
	case 3:
		Game_speechbubble("���� ����Ѵٰ�??? �� ����� ��� �ϴ� �Ŵ�??");
		break;
	}
}
