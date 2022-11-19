#include "SceneDimigo.h"

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

