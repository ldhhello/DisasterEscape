#include "SceneCafeteria.h"
#include "Game.h"

#include "SceneDimigo.h"

int scene_cafeteria_map[100][100] = {
	{ 0, 1, 1, 0, 0},
	{ 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 0, 1, 1, 1, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0}
};
int scene_cafeteria_x = 100, scene_cafeteria_y = 20;

Structure scene_cafeteria_structure[100];
int scene_cafeteria_struct_cnt = 0;

bool struct_loaded_cafeteria = 0;

Scene SceneCafeteria_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneCafeteria_load_map;
	scene.load_structure = SceneCafeteria_load_structure;
	scene.on_structure_active = SceneCafeteria_on_structure_active;
	scene.on_start = SceneCafeteria_on_start;

	scene.start_x = 19;
	scene.start_y = 11;
	scene.fixed_map = true;

	return scene;
}

int** cafeteria_map_return = NULL;

int** SceneCafeteria_load_map(int* x, int* y)
{
	*x = scene_cafeteria_x; *y = scene_cafeteria_y;

	if (cafeteria_map_return != NULL)
		return cafeteria_map_return;

	int** res = malloc(sizeof(int*) * (scene_cafeteria_y+10));

	for (int i = 0; i < scene_cafeteria_y+10; i++)
	{
		res[i] = scene_cafeteria_map[i];
		memset(scene_cafeteria_map[i], -1, sizeof(int) * scene_cafeteria_x);
	}

	return cafeteria_map_return = res;
}

Structure* SceneCafeteria_load_structure(int* sz)
{
	Structure* structure = scene_cafeteria_structure;

	Structure st[8] = {
		{2, -1, 0, 0, bitmap_cafeteria, false, true, NULL, 2.1},
		{10, 5, 1, 2, bitmap_house, false, false, SceneCafeteria_on_rice, 4},
		{14, 12, 7, 1, NULL, false, false, SceneCafeteria_on_door},
		//{15, 7, 4, 8, bitmap_house, false, true},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_cafeteria_struct_cnt = 5;
	*sz = scene_cafeteria_struct_cnt;

	if (struct_loaded_cafeteria)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_cafeteria = true;
	return structure;
}

void SceneCafeteria_on_start()
{
	Game_speechbubble("��, �����!");
	Game_speechbubble("���� ���� ���̴µ�, �Ծ��!");
}

void SceneCafeteria_on_door(int st, int dir)
{
	char str[2][100] = {
		"������", 
		"�ӹ�����"
	};

	if (Game_modal_select_box_speech("������ ��������?", str, 2) == 0)
		Game_change_scene(SceneDimigo_load(), false);
}

void SceneCafeteria_on_rice(int st, int dir)
{
	if (dir != UP)
		return;

	char str[9][100] = {
		"�Դ´�",
		"���� �ʴ´�",
		"������ ������",
		"��������",
		"���̾߶�� ��ġ��!",
		"���� ��� ����, ������ ������!",
		"ȭ��..? �װ� ����..? �Դ� �ǰ�?",
		"�׷�, �� ���� ���� ���. �޾Ƶ�����",
		"�׷��� ũ�� ���ĺ���"
	};


	char talk[3][100] = {
		"�Ծ��!",
		"����� ���� �Դ°� �ƴ� �� ����.",
		"������� ����? �Դ� �ǰ�?"
		//�亯
	};
	int result = Game_modal_select_box_speech("������� �Ծ��?", talk, 3);

	if (result == 0) {
		Game_speechbubble("�ʹ� ���ִ°�!\n\n���п� �踦 ä����!");
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
		
	} else if (result == 2){
		char oong[3][100] = {
		"�׷���..",
		"���Ⱑ �����?",
		"���� ������?"
		//�亯
		};
		if (Game_modal_select_box_speech("���� �ƴ°� ����?", oong, 3) < 10)
		{
			Game_system_message("������ �����Ϸ� �����ϴ�.");
			Game_die();
		
		}
	}
}

void SceneCafeteria_on_structure_active(int st, int dir)
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
		scene_cafeteria_structure[st].is_hide = true;

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

// �װų� ����� ������ ������ �����Ҷ� ȣ��Ǵ� �ڵ�
void SceneCafeteria_reset()
{
	struct_loaded_cafeteria = false;
	//is_first_cafeteria = true;
}