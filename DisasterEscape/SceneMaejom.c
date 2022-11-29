#include "SceneMaejom.h"
#include "Game.h"

#include "SceneDimigo.h"

int scene_maejom_map[100][100] = { 0, };
int scene_maejom_x = 100, scene_maejom_y = 20;
int quest_progress_maejom = 0;

Structure scene_maejom_structure[100];
int scene_maejom_struct_cnt = 0;

bool struct_loaded_maejom = 0;

Scene SceneMaejom_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.scene_id = SCENE_MAEJOM;

	scene.load_map = SceneMaejom_load_map;
	scene.load_structure = SceneMaejom_load_structure;
	scene.on_structure_active = SceneMaejom_on_structure_active;
	scene.on_start = SceneMaejom_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** maejom_map_return = NULL;

int** SceneMaejom_load_map(int* x, int* y)
{
	*x = scene_maejom_x; *y = scene_maejom_y;

	if (maejom_map_return != NULL)
		return maejom_map_return;

	int** res = malloc(sizeof(int*) * (scene_maejom_y + 10));

	for (int i = 0; i < scene_maejom_y + 10; i++)
	{
		res[i] = scene_maejom_map[i];
		memset(scene_maejom_map[i], -1, sizeof(int) * scene_maejom_x);
	}

	return maejom_map_return = res;
}

Structure* SceneMaejom_load_structure(int* sz)
{
	Structure* structure = scene_maejom_structure;

	Structure st[9] = {
		{2, -1, 0, 0, bitmap_maejom_inside, false, true, NULL, 2.1},
		{10, 6, 1, 1, bitmap_bibimbap, false, false, SceneMaejom_on_rice, 1.6},
		{19, 7, 1, 1, bitmap_towel, false, false, SceneMaejom_on_towel, 2},
		{5,10, 1, 1, bitmap_naoh, false, false, SceneMaejom_on_water, 2},

		{18, 3, 1, 1, bitmap_fire, true, true, NULL, 4.3},

		{0, 12, 21, 1, NULL, false, false, SceneMaejom_on_door},
		//{15, 7, 4, 8, bitmap_house, false, true},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_maejom_struct_cnt = 9;
	*sz = scene_maejom_struct_cnt;

	if (struct_loaded_maejom)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_maejom = true;
	return structure;
}

void SceneMaejom_on_start()
{
	if (quest_progress_maejom == 0)
	{
		Game_speechbubble("��, �����!");
		Game_speechbubble("���� ���� ���̴µ�, �Ծ��!");
	}

	outside_time += 10000;
}

void SceneMaejom_on_door(int st, int dir)
{
	char str[2][100] = {
		"������",
		"�ӹ�����"
	};

	if (Game_modal_select_box_speech("������ ��������?", str, 2) == 0)
	{
		if (quest_progress_maejom != 0 && quest_progress_maejom != 3)
		{
			Game_speechbubble("���� �� ����! ����!");
			Game_die();
			return;
		}

		Game_change_scene(SceneDimigo_load(), false);
	}
}

void SceneMaejom_on_rice(int st, int dir)
{
	if (dir != UP)
		return;

	if (quest_progress_maejom != 0)
		return;

	char talk[3][100] = {
		"�Ծ��!",
		"����� ���� �Դ°� �ƴ� �� ����.",
		"������� ����? �Դ� �ǰ�?"
		//�亯
	};
	int result = Game_modal_select_box_speech("������� �Ծ��?", talk, 3);

	if (result == 0) {
		Game_speechbubble("�ʹ� ���ִ°�!\n\n���п� �踦 ä����!");

		Sleep(1000);
		scene_maejom_structure[4].is_hide = false;
		Game_print_map(false);
		Sleep(1000);

		Game_speechbubble("��, ���� ����? �Ҳ��ΰ� ����!");

		char oong[3][100] = {
		"�׷�, �� ���� ���� ���. ��Ȳ�� �޾Ƶ�����.",
		"'���̾�'��� ũ�� ���ĺ���!",
		"���� ��� �Ǵ°ž�! ȥ�� ��������."
		//�亯
		};
		if (Game_modal_select_box_speech("�ݷ��ݷ�! ���̾�!", oong, 3) == 1)
		{
			Game_speechbubble("������ �ֺ� ��ΰ� ���� ��Ҹ��� ���� �� ����!");
			char oong_[2][100] = {
				"�������� ��ȭ����!",
				"119�� ��ȭ�ؼ� ȭ�� ����� �˸���!"
				//�亯
			};
			if (Game_modal_select_box_speech("���� ��� �ؾ� ����?", oong_, 2) == 1)
			{
				Game_speechbubble("�Ű��� �����߾�!\n\n���� ���� ������ ã���� ������!");

				Game_system_message("�޽Ľǿ��� ������ ã�ƺ���!");
				quest_progress_maejom = 1;
				return;
			}
			else {
				Game_system_message("������ ��ȭ�� �� �޾�!");
				Game_die();

			}

		}
		else {
			Game_system_message("ȭ�縦 �綧 �˸��� ������ ���� �θ����ط� �̾����ϴ�.");
			Game_die();

		}
	}
	else if (result == 1) {
		Game_speechbubble("��.. �谡 �ʹ� ����.");
		char oong[2][100] = {
		"���� ������ ���̾�. ����� �ð� �Ծ����!",
		"�谡 �ʹ� ���ļ� ���� �� ����. ����..",
		//�亯
		};
		if (Game_modal_select_box_speech("�ٽ� �ѹ� �����غ���. ������� ������?", oong, 2) < 10)
		{
			Game_system_message("���� �綧 ���� ���Ͽ� �ƻ��߽��ϴ�.");
			Game_die();

		}

	}
	else if (result == 2) {
		char oong[3][100] = {
		"1+1�� ����? 3�ΰ�?",
		"���Ⱑ �����?",
		"���� ������?"
		//�亯
		};
		if (Game_modal_select_box_speech("���� �ƴ°� ����?", oong, 3) < 10)
		{
			Game_system_message("������ �����ϱ� ���� ���������� �����ϴ�.");
			Game_die();

		}
	}
}

void SceneMaejom_on_towel(int st, int dir)
{
	if (quest_progress_maejom != 1)
	{
		Game_speechbubble("������ ���� �� ����?");
		return;
	}

	scene_maejom_structure[2].is_hide = true;
	Game_print_map(false);

	sleep_(300);

	Game_speechbubble("������ ã�Ҿ�! ���� ���� ã���� �� ����.");
	Game_system_message("�޽Ľǿ��� ���� ã�ƺ���!");

	quest_progress_maejom = 2;
}

void SceneMaejom_on_water(int st, int dir)
{
	if (quest_progress_maejom != 2)
	{
		char oong[3][100] = {
		"�λ��� �����̾�! ������ ���� ������!",
		"����..��? ���� ���ΰ� ������ �ٷ� ������!",
		"������ �� �ɰ� ����."
		//�亯
		};
		if (Game_modal_select_box_speech("���� ���� �� ����?\n\n�ڼ��� ���� �������̶�� ���� �־�.", oong, 3) < 2)
		{
			Game_speechbubble("����! �ʹ� ���ݾ�!\n\n����! ���� �� �� �̷�! ����! ũ��!");
			Game_system_message("�������� ���ø� ����� �̸� �� �ִ� ������ �����Դϴ�.");
			Game_die();
		}
		else {
			Game_speechbubble("��.. �Ծ����� ū�� �� �� �߾�.");
		}
		return;
	}

	scene_maejom_structure[3].is_hide = true;
	Game_print_map(false);

	sleep_(300);

	Game_speechbubble("���� ã�Ҿ�!");
	char oong_[3][100] = {
		"���� ���� ������ ������!",
		"����! ������ �ʹ� �ɸ����ŷ�. ������!",
		"��ħ ���� ������ ���Ź�����!"
		//�亯
	};

	int whatt = Game_modal_select_box_speech("���� ��� �ؾ� ����?", oong_, 3);
	if (whatt == 0)
	{
		Game_speechbubble("�Ʒ������� �������� ������ ������!");

		Game_set_return(RETURNVAL_MAEJOM_MISSION);
		quest_progress_maejom = 3;
		//Game_change_scene(SceneDimigo_load(), false);
		return;
	}
	else if (whatt == 1) {
		Game_system_message("ȭ�� ��Ȳ���� ���� ������ ������ ���� ���⸦ �����ϱ⿡ ���� ȿ������ �����Դϴ�.");
		Game_die();
	}
	else {
		Game_speechbubble("���.. ���� ����� ���� �ִ°���? ��..����?");
		Game_speechbubble("����! �ʹ� ���ݾ�!\n\n����! ���� �� �� �̷�! ����! ũ��!");
		Game_system_message("�������� ���ø� ����� �̸� �� �ִ� ������ �����Դϴ�.");
		Game_die();
	}


}

void SceneMaejom_on_structure_active(int st, int dir)
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
		scene_maejom_structure[st].is_hide = true;

		sleep_(100);
		Game_print_map(false);
		sleep_(500);

		Game_speechbubble("���� ��ƸԾ���!!");

		break;
	case 3:
		Game_speechbubble("���� ����Ѵٰ�??? �� ����� ��� �ϴ� �Ŵ�??");
		break;
	}
}

// �װų� ����� ������ ������ �����Ҷ� ȣ��Ǵ� �ڵ�
void SceneMaejom_reset()
{
	struct_loaded_maejom = false;
	quest_progress_maejom = 0;
	//is_first_maejom = true;
}