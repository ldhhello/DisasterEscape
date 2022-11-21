#include "SceneDimigo.h"
#include "Game.h"

#include "SceneCafeteria.h"

int scene_dimigo_map[100][100] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},//5
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},//10
	{0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},//15
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1}
};
int scene_dimigo_x = 100, scene_dimigo_y = 100;

int cafeteria_health = 100;

Structure scene_dimigo_structure[100];
int scene_dimigo_struct_cnt = 0;
bool struct_loaded_dimigo = false;

bool is_first_dimigo = true;

Scene SceneDimigo_load()
{
	Scene scene;
	memset(&scene, 0, sizeof(Scene));

	scene.load_map = SceneDimigo_load_map;
	scene.load_structure = SceneDimigo_load_structure;
	scene.on_structure_active = SceneDimigo_on_structure_active;
	scene.on_start = SceneDimigo_on_start;
	scene.on_return = SceneDimigo_on_return;
	scene.on_key_pressed = SceneDimigo_on_key_pressed;

	scene.start_x = 10; scene.start_y = 10;

	return scene;
}

int** dimigo_map_return;

int** SceneDimigo_load_map(int* x, int* y)
{
	*x = scene_dimigo_x; *y = scene_dimigo_y;
	
	if (dimigo_map_return != NULL)
		return dimigo_map_return;

	int** res = malloc(sizeof(int*) * scene_dimigo_y);

	for (int i = 0; i < scene_dimigo_y; i++)
	{
		res[i] = scene_dimigo_map[i];
	}

	return dimigo_map_return = res;
}

Structure* SceneDimigo_load_structure(int* sz)
{
	Structure* structure = scene_dimigo_structure;

	Structure st[9] = {
		{3, 15, 6, 8, bitmap_hakbonggwan, false, false, SceneDimigo_on_hakbonggwan, 4},
		{3, 1, 6, 10, bitmap_bongwan1, false, false, SceneDimigo_on_active_cafeteria, 4.5},
		{9, 1, 8, 4, bitmap_bongwan2, false, false, SceneDimigo_on_bongwan, 4.5},
		{20, 1, 12, 9, bitmap_singwan, false, false, SceneDimigo_on_singwan, 4.5},
		{3, 24, 4, 8, bitmap_house, false, true, NULL, 1},
		{7, 7, 0, 0, bitmap_water, true, true, NULL, 2},
		{3, 11, 1, 4, NULL, false, false, SceneDimigo_on_door},
		{9, 22, 3, 1, NULL, false, false, SceneDimigo_on_door},
		{37, 0, 1, 20, NULL, false, false, SceneDimigo_on_ujunghaksa}
	};

	scene_dimigo_struct_cnt = 9;
	*sz = scene_dimigo_struct_cnt;

	if (struct_loaded_dimigo)
		return structure;

	memcpy(structure, st, sizeof(st));

	struct_loaded_dimigo = true;
	return structure;
}

void SceneDimigo_on_return(int ret)
{
	if (ret == RETURNVAL_CAFETERIA_MISSION)
	{
		// 본관 불타는 이미지 1
		//scene_dimigo_structure[1].bitmap = bitmap_bongwan[4][0];
		//scene_dimigo_structure[2].bitmap = bitmap_bongwan[4][1];
		cafeteria_health = 50;
		SceneDimigo_change_cafeteria_skin();
		Game_print_map(false);

		Game_speechbubble("휴.. 밖으로 나왔다. 하마터면 죽을 뻔했어.");
		Game_speechbubble("소방관을 도와 불을 꺼보자!\n\n[N]키를 누르면 물을 발사할 수 있어.");
		quest_progress_cafeteria = 10;
		return;
	}
}

void SceneDimigo_on_start()
{
	if (!is_first_dimigo)
		return;

	is_first_dimigo = false;

	Game_speechbubble("나는 1학년 7반 김산천.");
	Game_speechbubble("오늘 학교에 입학해서 아직 아무것도 모르겠다.");
	Game_speechbubble("학교를 탐방해보면서 학교에 대해서 익혀봐야겠군!");
}

void SceneDimigo_change_cafeteria_skin()
{
	if (70 < cafeteria_health && cafeteria_health <= 100)
	{
		scene_dimigo_structure[1].bitmap = bitmap_bongwan[4][0];
		scene_dimigo_structure[2].bitmap = bitmap_bongwan[4][1];
	}
	else if (50 < cafeteria_health && cafeteria_health <= 70)
	{
		scene_dimigo_structure[1].bitmap = bitmap_bongwan[3][0];
		scene_dimigo_structure[2].bitmap = bitmap_bongwan[3][1];
	}
	else if (20 < cafeteria_health && cafeteria_health <= 50)
	{
		scene_dimigo_structure[1].bitmap = bitmap_bongwan[2][0];
		scene_dimigo_structure[2].bitmap = bitmap_bongwan[2][1];
	}
	else if (0 < cafeteria_health && cafeteria_health <= 20)
	{
		scene_dimigo_structure[1].bitmap = bitmap_bongwan[1][0];
		scene_dimigo_structure[2].bitmap = bitmap_bongwan[1][1];
	}
}

void SceneDimigo_on_key_pressed(char ch)
{
	if ((ch == 'n' || ch == 'N') && quest_progress_cafeteria == 10)
	{
		//Game_speechbubble("왠지 불을 끌수 있을것 같은 버튼이다!");

		if (player_idx != 0)
			return;

		scene_dimigo_structure[5].x = player_x; scene_dimigo_structure[5].y = player_y-2;

		scene_dimigo_structure[5].is_hide = false;
		Game_print_map(false);

		Sleep(50);

		scene_dimigo_structure[5].is_hide = true;
		Game_print_map(false);

		cafeteria_health -= 5;

		if (cafeteria_health <= 0)
		{
			scene_dimigo_structure[1].bitmap = bitmap_bongwan[0][0];
			scene_dimigo_structure[2].bitmap = bitmap_bongwan[0][1];
			Game_print_map(false);

			Game_speechbubble("와 불길이 멈췄어!!");
			Game_speechbubble("와샌즈!@!@#@@@");

			Game_system_message("퀘스트 완료: 급식실 화재");

			quest_progress_cafeteria = 11;
		}
	}
}

void SceneDimigo_on_tick()
{
	if (quest_progress_cafeteria == 10)
	{
		cafeteria_health++;
		SceneDimigo_change_cafeteria_skin();
		Game_print_map(false);
	}
}

void SceneDimigo_on_active_cafeteria(int st, int dir)
{
	if (dir == LEFT)
	{
		SceneDimigo_on_bongwan(st, UP);
		return;
	}

	if (dir != UP)
		return;

	char str[2][100] = { "들어가보자!","아니야, 안 갈래."};

	if (Game_modal_select_box_speech("맛있는 냄새가 난다!\n\n급식실에 들어가볼까?", str, 2) == 0)
	{
		if (quest_progress_cafeteria == 10)
		{
			Game_speechbubble("으악! 뜨거워!");

			Game_die();
			return;
		}

		//image_layer.fadeOut(&image_layer, NULL);
		//Sleep(1000);

		Game_change_scene(SceneCafeteria_load(), true);
	}
}

void SceneDimigo_on_bongwan(int st, int dir)
{
	if (dir != UP)
		return;

	Game_speechbubble("오, 이 건물이 디미고 본관인가봐!");
	char oong[2][100] = {
		"여기는 문이 아닌데, 벽을 부시고 들어갈까?",
		"들어가지 말자.",
		//답변
	};
	if (Game_modal_select_box_speech("들어가 볼까?", oong, 2) == 0)
	{
		Game_speechbubble("으악!!!!!");
		Game_print_earthquake(1000);
		Game_system_message("벽에 돌진하면 심각한 부상을 입을 수 있습니다.");
		Game_die();
		return;
	}
	else {
		char oong[3][100] = {
		"피하지 말고 즐기자!",
		"배가 아픈 것 같아. 빨리 돌아가야겠어.",
		"아니야. 하지 말자"
		//답변
		};
		if (Game_modal_select_box_speech("그래도 재밌을 것 같아. 다시 한번 생각해보자!", oong, 3) == 0)
		{
			Game_speechbubble("으악!!!!!");
			Game_print_earthquake(1000);
			Game_system_message("벽에 돌진하면 심각한 부상을 입을 수 있습니다.");
			Game_die();
			return;
		}
		else {
			Game_speechbubble("살았다.");
		}
	}
}

void SceneDimigo_on_hakbonggwan(int st, int dir)
{
	if (dir != LEFT)
		return;

	Game_speechbubble("여기는 우리들의 보금자리 학봉관이군!");
	Game_system_message("주현준의 집이기도 하다");
}

void SceneDimigo_on_door(int st, int dir)
{
	Game_speechbubble("학교 밖으로 나가면 안 될것 같아!");
}

void SceneDimigo_on_ujunghaksa(int st, int dir)
{ 
	char str[2][100] = { "들어가보자!","위험한 것 같아. 돌아가자." };

	if (Game_modal_select_box_speech("저기 팻말에 뭐라고 써져있는 거지?\n\n도.. 서관 공사중?", str, 2) == 0)
	{
		Game_system_message("공사중인 장소에 들어가는 것은 매우 위험한 행동입니다.");
		Game_die();
	}
}

void SceneDimigo_on_singwan(int st, int dir)
{
	if (dir == UP)
	{
		Game_speechbubble("이 건물은 3학년들이 있는 신관이구나!");
		return;
	}
	else if (dir == LEFT)
	{
		Game_speechbubble("엇, 여기는 매점인가 봐! 아쉽지만 닫혀 있네.");
	}
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
		//Game_speechbubble("집을 잡아먹는다고??? 난 못 먹어..");
		scene_dimigo_structure[st].is_hide = true;

		Sleep(100);
		Game_print_map(false);
		Sleep(1000);

		Game_speechbubble("집을 잡아먹었다!!");

		break;
	case 3:
		Game_speechbubble("집을 사용한다고??? 집 사용은 어떻게 하는 거니??");
		break;
	}
}

// 죽거나 등등의 이유로 게임을 종료할때 호출되는 코드
void SceneDimigo_reset()
{
	struct_loaded_dimigo = false;
	is_first_dimigo = true;
}