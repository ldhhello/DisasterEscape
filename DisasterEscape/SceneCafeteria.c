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
int quest_progress_cafeteria = 0;

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
		{10, 6, 1, 1, bitmap_bibimbap, false, false, SceneCafeteria_on_rice, 1.6},
		{10, 10, 1, 1, bitmap_towel, false, false, SceneCafeteria_on_towel, 2},
		{6, 8, 1, 1, bitmap_naoh, false, false, SceneCafeteria_on_water, 2},

		{0, 12, 21, 1, NULL, false, false, SceneCafeteria_on_door},
		//{15, 7, 4, 8, bitmap_house, false, true},
		//{17, 14, 4, 8, bitmap_house},
		{0, 12, 14, 1, NULL},
		{1, 0, 1, 20, NULL},
		{21, 0, 1, 20, NULL}
	};

	scene_cafeteria_struct_cnt = 8;
	*sz = scene_cafeteria_struct_cnt;

	if (struct_loaded_cafeteria)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_cafeteria = true;
	return structure;
}

void SceneCafeteria_on_start()
{
	if (quest_progress_cafeteria == 0)
	{
		Game_speechbubble("아, 배고파!");
		Game_speechbubble("저기 밥이 보이는데, 먹어보자!");
	}
}

void SceneCafeteria_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기", 
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
		Game_change_scene(SceneDimigo_load(), false);
}

void SceneCafeteria_on_rice(int st, int dir)
{
	if (dir != UP)
		return;

	if (quest_progress_cafeteria != 0)
		return;

	char str[9][100] = {
		"먹는다",
		"먹지 않는다",
		"가까이 가본다",
		"도망간다",
		"불이야라고 외치자!",
		"나만 살면 되지, 조용히 도망가!",
		"화재..? 그게 뭐지..? 먹는 건가?",
		"그래, 이 또한 나의 운명. 받아들이자",
		"그래도 크게 외쳐보자"
	};


	char talk[3][100] = {
		"먹어보자!",
		"허락도 없이 먹는건 아닌 것 같아.",
		"비빔밥이 뭐지? 먹는 건가?"
		//답변
	};
	int result = Game_modal_select_box_speech("비빔밥을 먹어볼까?", talk, 3);

	if (result == 0) {
		Game_speechbubble("너무 맛있는걸!\n\n덕분에 배를 채웠어!");
		Game_speechbubble("엇, 저게 뭐지? 불꽃인것 같아!");
		
		char oong[3][100] = {
		"그래, 이 또한 나의 운명. 상황을 받아들이자.",
		"'불이야'라고 크게 외쳐보자!",
		"나만 살면 되는거야! 혼자 도망가자."
		//답변
		};
		if (Game_modal_select_box_speech("콜록콜록! 불이야!", oong, 3) == 1)
		{
			Game_speechbubble("다행히 주변 모두가 나의 목소리를 들은 것 같아!");
			char oong_[2][100] = {
				"엄마한테 전화하자!", 
				"119에 전화해서 화재 사실을 알리자!"
				//답변
			};
			if (Game_modal_select_box_speech("이제 어떻게 해야 하지?", oong_, 2) == 1)
			{
				Game_speechbubble("신고에 성공했어!\n\n이제 젖은 수건을 찾으러 가보자!");

				Game_system_message("급식실에서 수건을 찾아보자!");
				quest_progress_cafeteria = 1;
				return;
			}
			else {
				Game_system_message("엄마가 전화를 안 받아!");
				Game_die();

			}

		}
		else {
			Game_system_message("화재를 재때 알리지 않아 대형 인명피해로 이어졌습니다.");
			Game_die();

		}
	}
	else if (result == 1) {
		Game_speechbubble("윽.. 배가 너무 고파.");
		char oong[2][100] = {
		"나는 정직한 아이야. 허락을 맡고 먹어야지!",
		"배가 너무 고파서 앞이 안 보여. 으윽..",
		//답변
		};
		if (Game_modal_select_box_speech("다시 한번 생각해보자. 비빔밥을 먹을까?", oong, 2) < 10)
		{
			Game_system_message("밥을 재때 먹지 못하여 아사했습니다.");
			Game_die();

		}
		
	} else if (result == 2){
		char oong[3][100] = {
		"1+1은 뭘까? 3인가?",
		"여기가 어디지?",
		"나는 누구지?"
		//답변
		};
		if (Game_modal_select_box_speech("나는 아는게 뭘까?", oong, 3) < 10)
		{
			Game_system_message("지식을 수양하기 위해 광덕산으로 떠납니다.");
			Game_die();
		
		}
	}
}

void SceneCafeteria_on_towel(int st, int dir)
{
	if (quest_progress_cafeteria != 1)
	{
		Game_speechbubble("수건이 여기 왜 있지?");
		return;
	}

	scene_cafeteria_structure[2].is_hide = true;
	Game_print_map(false);

	Sleep(300);

	Game_speechbubble("수건을 찾았어! 이제 물을 찾으러 가 보자.");
	Game_system_message("급식실에서 물을 찾아보자!");

	quest_progress_cafeteria = 2;
}

void SceneCafeteria_on_water(int st, int dir)
{
	if (quest_progress_cafeteria != 2)
	{
		char oong[3][100] = {
		"인생은 스릴이야! 피하지 말고 마시자!",
		"양잿..물? 좋은 물인것 같으니 바로 마시자!",
		"먹으면 안 될것 같아."
		//답변
		};
		if (Game_modal_select_box_speech("여기 물이 왜 있지?\n\n자세히 보니 양잿물이라고 적혀 있어.", oong, 3) < 2)
		{
			Game_speechbubble("우웩! 너무 쓰잖아!\n\n켁켁! 맛은 또 왜 이래! 우웩! 크억!");
			Game_system_message("양잿물은 마시면 사망에 이를 수 있는 위험한 물질입니다.");
			Game_die();
		}else{
			Game_speechbubble("휴.. 먹었으면 큰일 날 뻔 했어.");
		}
		return;
	}

	scene_cafeteria_structure[3].is_hide = true;
	Game_print_map(false);

	Sleep(300);

	Game_speechbubble("물을 찾았어!");
	char oong_[2][100] = {
		"입을 막고 밖으로 나가자!",
		"아잇! 수건이 너무 걸리적거려. 버리자!"
		//답변
	};
	if (Game_modal_select_box_speech("이제 어떻게 해야 하지?", oong_, 2) == 0)
	{
		Game_speechbubble("아래쪽으로 내려가서 밖으로 나가자!");

		Game_set_return(RETURNVAL_CAFETERIA_MISSION);
		quest_progress_cafeteria = 3;
		//Game_change_scene(SceneDimigo_load(), false);
		return;
	}
	else {
		Game_system_message("화재 상황에서 젖은 수건은 입으로 들어가는 연기를 차단하기에 가장 효과적인 수단입니다.");
		Game_die();
	}

	
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
	quest_progress_cafeteria = 0;
	//is_first_cafeteria = true;
}