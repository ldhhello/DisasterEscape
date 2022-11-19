#include "SceneDimigo.h"
#include "Game.h"

int scene_dimigo_map[100][100] = {
	{ 0, 1, 1, 0, 0},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0},
	{ 0, 1, 1, 0, 0}
};
int scene_dimigo_x = 100, scene_dimigo_y = 100;

Structure scene_dimigo_structure[100];
int scene_dimigo_struct_cnt = 0;

Scene SceneDimigo_load()
{
	Scene scene;

	scene.load_map = SceneDimigo_load_map;
	scene.load_structure = SceneDimigo_load_structure;
	scene.on_structure_active = SceneDimigo_on_structure_active;
	scene.on_start = SceneDimigo_on_start;

	return scene;
}

// �� �ڵ� ��� �޸� ���� ������ �ִ�!
// �׷��� ������ �� �ε��� �ѹ��ۿ� ���ϴϱ� �ణ ���� ���� ��� ���� �� ����
// ���� ����� ���߿� ��ġ�� ��,,
int** SceneDimigo_load_map(int* x, int* y)
{
	int** res = malloc(sizeof(int*) * scene_dimigo_y);

	for (int i = 0; i < scene_dimigo_y; i++)
	{
		res[i] = scene_dimigo_map[i];
	}

	*x = scene_dimigo_x; *y = scene_dimigo_y;

	return res;
}

Structure* SceneDimigo_load_structure(int* sz)
{
	Structure* structure = scene_dimigo_structure;

	Structure st[5] = {
		{3, 5, 4, 8, bitmap_house},
		{10, 5, 4, 8, bitmap_house},
		{15, 7, 4, 8, bitmap_house},
		{17, 14, 4, 8, bitmap_house},
		{3, 24, 4, 8, bitmap_house}
	};

	scene_dimigo_struct_cnt = 5;
	*sz = scene_dimigo_struct_cnt;

	memcpy(structure, st, sizeof(st));

	return structure;
}

void SceneDimigo_on_start()
{
	Game_speechbubble("���̸��� ������.");
	Game_speechbubble("��̰� ���� ���� ������.");
	Game_speechbubble("�����!!!!@!@!@!@!@!");
}

void SceneDimigo_on_structure_active(int st, int dir)
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
		break;
	case 2:
		//Game_speechbubble("���� ��ƸԴ´ٰ�??? �� �� �Ծ�..");
		scene_dimigo_structure[st].is_hide = true;

		Sleep(100);
		Game_print_map();
		Sleep(500);

		Game_speechbubble("���� ��ƸԾ���!!");

		break;
	case 3:
		Game_speechbubble("���� ����Ѵٰ�??? �� ����� ��� �ϴ� �Ŵ�??");
		break;
	}
}