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
		Game_speechbubble("휴, 이제야 마음이 놓이네!");
		Game_speechbubble("공기 청정기를 켜서 공기를 정화시켜 보자.");
		quest_progress_bongwan = 2;
	}
}//

void SceneBongwan_on_table(int st, int dir)
{
	if (quest_progress_bongwan == 3)
	{

		Game_print_earthquake(1000);


		char oonng[3][100] = {
			"뭘 가디려! 그냥 뛰어 나가!",
			"지진따위 두렵지 않아!!",
			"침착하게 지진이 끝날 때까지 기다리자."
			//답변
		};


		if (Game_modal_select_box_speech("책상 밑으로 왔으니 이제 진동이 멈출 때까지 기다리자!", oonng, 3) != 2)
		{
			Game_print_earthquake(1000);
			Game_system_message("지진 상황에서 섣불리 움직이는 것은\n\n매우 위험한 행동입니다.");
			Game_die();
			return;

		}
		else {
			char ooonng[3][100] = {
			"엄마한테 전화하자!",
			"화장실로 가서 숨자!",
			"출입문 쪽으로 빠르게 나가자!"
			//답변
			};


			if (Game_modal_select_box_speech("진동이 멈춘 것 같아! 이제 어떻게 하지?", ooonng, 3) != 2)
			{
				Game_print_earthquake(1000);
				Game_system_message("진동이 멈추면 최대한 신속하게 나가야 합니다.");
				Game_die();
				return;

			}
			else {
				Game_system_message("건물 밖으로 대피하세요!");
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
		"전기 아까워! 먼지 필터는 코털로도 충분해.",
		"어서 공기 청정기를 켜 보자!",
		"공기 청정? 기? 그게 뭐지?"
		//답변
		};
		if (Game_modal_select_box_speech("공기 청정기를 켜 볼까?", oong, 3) != 1)
		{
			Game_system_message("숨이 안 쉬어져!");
			Game_die();
			return;

		}
		else {
			Game_speechbubble("이제야 살 것 같아!");
			Game_system_message("퀘스트 완료: 초고농도 미세먼지");

			Game_print_earthquake(1000);

			Game_speechbubble("누가 핸드폰을 진동으로 해 두었나 봐.\n\n왜 이렇게 흔들리지?");

			char oonng[3][100] = {
				"지진, 까짓거 몸으로 맞자!",
				"엄마한테 가야겠어!",
				"책상 밑으로 재빠르게 들어가자!"
				//답변
			};


			if (Game_modal_select_box_speech("엇, 이건 휴대폰 진동이 아닌 지진이잖아!", oonng, 3) != 2)
			{
				Game_print_earthquake(1000);
				Game_system_message("지진 상황에서 섣불리 움직이는 것은\n\n매우 위험한 행동입니다.");
				Game_die();
				return;

			}
			else {
				Game_system_message("책상 밑으로 이동하세요!");
				quest_progress_bongwan = 3;
			}
		}
	}
}

void SceneBongwan_on_door(int st, int dir)
{
	char str[2][100] = {
		"나가기",
		"머무르기"
	};

	if (Game_modal_select_box_speech("밖으로 나가볼까?", str, 2) == 0)
	{
		if (quest_progress_bongwan != 0 && quest_progress_bongwan != 4)
		{
			Game_speechbubble("으악! 건물이 무너지고 있어!!");
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
		scene_bongwan_structure[st].is_hide = true;

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
