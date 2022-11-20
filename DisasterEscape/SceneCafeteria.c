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
	Game_speechbubble("아 배고프다.");
	Game_speechbubble("앗, 저기 밥이 보인다!");
}

void SceneCafeteria_on_door(int st, int dir)
{
	char str[1][100] = {
		"나가기"
	};

	if (Game_modal_select_box_speech("밖으로 나갈까?", str, 1) == 0)
		Game_change_scene(SceneDimigo_load(), false);
}

void SceneCafeteria_on_rice(int st, int dir)
{
	if (dir != UP)
		return;

	char str[9][100] = {
		"먹는다",
		"먹지 않는다", // 일단 이렇게 테스트하고 가변길이 텍스트 하고 하는걸로
		"가까이 가본다",
		"도망간다",
		"불이야라고 외치자!",
		"나만 살면 되지, 조용히 도망가!",
		"화재..? 그게 뭐지..? 먹는 건가?",
		"그래, 이 또한 나의 운명. 받아들이자",
		"그래도 크게 외쳐보자"
	};

goto_a:
	switch (Game_modal_select_box_speech("밥을 먹을까?", str, 2))
	{
	case 0:
		Game_speechbubble("냠냠...");
		break;
	case 1:
		Game_speechbubble("윽.. 배고파..");
		Game_speechbubble("굶어 죽을 것 같아..");

		Game_die();
		return;
	default:
		goto goto_a;
	}
	
	image_layer.renderAll(&image_layer);
	Sleep(2000);

goto_b:
	switch (Game_modal_select_box_speech("어, 저쪽에 빨간 불꽃이 있다. 저게 뭐지?", str+2, 2))
	{
	case 0: // 가까이 가보기
		break;
		
	case 1:
		//Game_speechbubble("도망가야 할 것 같아!");
		//Game_set_return(RETURNVAL_CAFETERIA_MISSION);
		//Game_change_scene(SceneDimigo_load(), false);

		goto goto_d;

		break;

	default:
		goto goto_b;
	}

	Sleep(1000);

goto_c:
	switch (Game_modal_select_box_speech("콜록콜록! 저건 연기잖아! 화재가 발생한 것 같아.", str + 4, 3))
	{
	case 0: // 불이야라고 외치자!
		Game_speechbubble("어제 노래방에서 노래를 너무 크게 불렀더니 목소리가 안 나온다.");
		break;
	case 1: // 나만 살면 되지. 조용히 도망가!
		Game_speechbubble("너무 조용히 나가서 구조대원에 발견되지 못했다!");
		// 일단 임시로 이 선택지는 여기까지

		Game_die();
		return;
		break;
	case 2:
		
	default:
		goto goto_c;
	}

goto_d:
	switch (Game_modal_select_box_speech("어제 노래 적당히 부를걸! 이제 어떡하지?", str + 7, 2))
	{
	case 0: // 나의 운명, 받아들이자
		Game_die();
		return;
	case 1:
		break;
	default:
		goto goto_d;
	}

	return;
}

void SceneCafeteria_on_structure_active(int st, int dir)
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
		Game_die();
		break;
	case 2:
		//Game_speechbubble("집을 잡아먹는다고??? 난 못 먹어..");
		scene_cafeteria_structure[st].is_hide = true;

		Sleep(100);
		Game_print_map(false);
		Sleep(500);

		Game_speechbubble("집을 잡아먹었다!!");

		break;
	case 3:
		Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
		break;
	}
}

// 죽거나 등등의 이유로 게임을 종료할때 호출되는 코드
void SceneCafeteria_reset()
{
	struct_loaded_cafeteria = false;
	//is_first_cafeteria = true;
}