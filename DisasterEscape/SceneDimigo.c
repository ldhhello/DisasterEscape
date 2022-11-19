#include "SceneDimigo.h"
#include "Game.h"

int scene_dimigo_map[100][100] = {
	{ 0, 0, 1, 0, 0},
	{ 0, 1, 0, 1, 0},
	{ 1, 0, 0, 0, 1},
	{ 0, 1, 0, 1, 0},
	{ 0, 0, 1, 0, 0},
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

	return scene;
}

// 이 코드 사실 메모리 누수 문제가 있다!
// 그런데 어차피 맵 로딩은 한번밖에 안하니까 약간 누수 나도 상관 없을 것 같다
// 문제 생기면 나중에 고치지 머,,
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

	Structure st = { 3, 5, 4, 8, bitmap_house };
	scene_dimigo_structure[0] = st;

	st.x += 7;
	scene_dimigo_structure[1] = st;
	
	st.x += 7;
	scene_dimigo_structure[2] = st;

	st.x += 7;
	scene_dimigo_structure[3] = st;

	st.x += 7;
	scene_dimigo_structure[4] = st;

	scene_dimigo_struct_cnt = 5;
	*sz = scene_dimigo_struct_cnt;

	return structure;
}

void SceneDimigo_on_structure_active(int st, int dir)
{
	if (dir != UP)
		return;

	char str[4][100] = {
					"들어가기",
					"도망가기",
					"잡아먹기",
					"사용하기"
	};

	switch (Game_modal_select_box_speech("집이다! 들어갈까?", str, 4))
	{
	case 0:
		Game_speechbubble("들어가는데 실패했다!");
		break;
	case 1:
		Game_speechbubble("도망가는데 실패했다!");
		break;
	case 2:
		Game_speechbubble("집을 잡아먹는다고??? 난 못 먹어..");
		break;
	case 3:
		Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
		break;
	}
}