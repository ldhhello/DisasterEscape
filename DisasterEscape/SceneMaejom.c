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
		{2, -7, 0, 0, bitmap_maejom_inside, false, true, NULL, 1.6},
		{7, 5, 2, 2, bitmap_dimigang, false, false, SceneMaejom_on_snack, 0.4},
		{19, 8, 1, 1, bitmap_towel, false, false, SceneMaejom_on_towel, 2},
		{8, 10, 1, 2, bitmap_aloe, false, false, SceneMaejom_on_water, 0.5},

		{18, 3, 4, 4, bitmap_fire, true, false, SceneMaejom_on_fire, 4.3},

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
		Game_speechbubble("여기가 매점인가 봐!");
	}

	outside_time += 10000;
}

void SceneMaejom_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
	{
		if (quest_progress_maejom != 0 && quest_progress_maejom != 3)
		{
			Game_speechbubble("문이 안 열려! 으악!");
			Game_die();
			return;
		}

		Game_change_scene(SceneDimigo_load(), false);
	}
}

void SceneMaejom_on_snack(int st, int dir)
{
	if (quest_progress_maejom != 0)
		return;

	char talk[2][100] = {
		"맛있겠다! 먹자!",
		"뒤에 누가 있어!",
		//답변
	};
	int result = Game_modal_select_box_speech("디미깡을 먹을까?", talk, 3);

	if (result == 0) {
		Game_speechbubble("냠냠.");

		Sleep(1000);
		scene_maejom_structure[4].is_hide = false;
		Game_print_map(false);
		Sleep(1000);

		Game_speechbubble("새로 나온 불과자인가봐!\n\n어서 먹자!");

		char oong[3][100] = {
		"저건 과자가 아니고 화재야!",
		"오히려 좋아! 이열치열!",
		"모르겠고 먹자!"
		//답변
		};
		if (Game_modal_select_box_speech("근데, 과자가 뜨겁고 연기가 나는데?", oong, 3) == 0)
		{
			Game_speechbubble("어서 신고해서 화재 발생을 알려야겠어!");
			char oong_[2][100] = {
				"교육청에 신고하자!",
				"119에 전화하자!"
				//답변
			};
			if (Game_modal_select_box_speech("이제 어떻게 해야 하지?", oong_, 2) == 1)
			{
				Game_speechbubble("신고에 성공했어!\n\n이제 젖은 수건을 찾으러 가보자!");

				Game_system_message("매점에서 수건을 찾아보자!");
				quest_progress_maejom = 1;
				return;
			}
			else {
				Game_system_message("엄마가 전화를 안 받아!");
				Game_die();

			}

		}
		else {
			Game_system_message("화재 상황에서 불꽃을 과자로 오인한다면 \n\n큰 피해로 이어질 수 있습니다.");
			Game_die();

		}
	}
	else if (result == 1) {
		Game_system_message("으악!");
		Game_die();

	}
}

void SceneMaejom_on_towel(int st, int dir)
{
	if (quest_progress_maejom != 1)
	{
		Game_speechbubble("수건이 여기 왜 있지?");
		return;
	}

	scene_maejom_structure[2].is_hide = true;
	Game_print_map(false);

	sleep_(300);

	Game_speechbubble("수건을 찾았어! 이제 물을 찾으러 가 보자.");
	Game_system_message("급식실에서 물을 찾아보자!");

	quest_progress_maejom = 2;
}

void SceneMaejom_on_water(int st, int dir)
{
	if (quest_progress_maejom != 2)
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
		}
		else {
			Game_speechbubble("휴.. 먹었으면 큰일 날 뻔 했어.");
		}
		return;
	}

	scene_maejom_structure[3].is_hide = true;
	Game_print_map(false);

	sleep_(300);

	Game_speechbubble("물을 찾았어!");
	char oong_[3][100] = {
		"입을 막고 밖으로 나가자!",
		"아잇! 수건이 너무 걸리적거려. 버리자!",
		"마침 목이 마른데 마셔버리자!"
		//답변
	};

	int whatt = Game_modal_select_box_speech("이제 어떻게 해야 하지?", oong_, 3);
	if (whatt == 0)
	{
		Game_speechbubble("아래쪽으로 내려가서 밖으로 나가자!");

		Game_set_return(RETURNVAL_MAEJOM_MISSION);
		quest_progress_maejom = 3;
		//Game_change_scene(SceneDimigo_load(), false);
		return;
	}
	else if (whatt == 1) {
		Game_system_message("화재 상황에서 젖은 수건은 입으로 들어가는 연기를 차단하기에 가장 효과적인 수단입니다.");
		Game_die();
	}
	else {
		Game_speechbubble("잠깐만.. 병에 뭐라고 써져 있는거지? 양..잿물?");
		Game_speechbubble("우웩! 너무 쓰잖아!\n\n켁켁! 맛은 또 왜 이래! 우웩! 크억!");
		Game_system_message("양잿물은 마시면 사망에 이를 수 있는 위험한 물질입니다.");
		Game_die();
	}


}

void SceneMaejom_on_fire(int st, int dir)
{
	Game_speechbubble("으악 뜨거워!!");
	Game_system_message("화재 상황에서 불에 가까이 다가가면 화상을 입을수 있습니다.");
	Game_die();
}

void SceneMaejom_on_structure_active(int st, int dir)
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
		scene_maejom_structure[st].is_hide = true;

		sleep_(100);
		Game_print_map(false);
		sleep_(500);

		Game_speechbubble("집을 잡아먹었다!!");

		break;
	case 3:
		Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
		break;
	}
}

// 죽거나 등등의 이유로 게임을 종료할때 호출되는 코드
void SceneMaejom_reset()
{
	struct_loaded_maejom = false;
	quest_progress_maejom = 0;
	//is_first_maejom = true;
}