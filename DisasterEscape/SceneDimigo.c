#include "SceneDimigo.h"
#include "Game.h"

#include "SceneCafeteria.h"
#include "SceneBongwan.h"
#include "SceneHakbonggwan.h"
#include "SceneSingwan.h"

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
	scene.on_tick = SceneDimigo_on_tick;

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

	Structure st[13] = {
		{3, 15, 6, 8, bitmap_hakbonggwan, false, false, SceneDimigo_on_hakbonggwan, 4},
		{3, 1, 6, 10, bitmap_bongwan1, false, false, SceneDimigo_on_active_cafeteria, 4.5},
		{9, 1, 8, 4, bitmap_bongwan2, false, false, SceneDimigo_on_bongwan, 4.5},
		{20, 1, 12, 9, bitmap_singwan, false, false, SceneDimigo_on_singwan, 4.5},
		{3, 24, 4, 8, bitmap_house, false, true, NULL, 1},
		{7, 7, 0, 0, bitmap_water, true, true, NULL, 2},
		{11, 13, 0, 0, bitmap_gangdang, false, true, NULL, 4},
		{12, 22, 50, 1, NULL, false, false, NULL},
		{32, 6, 5, 1, NULL, false, false, NULL},
		{17, 1, 3, 1, NULL, false, false, SceneDimigo_on_door},
		{3, 11, 1, 4, NULL, false, false, SceneDimigo_on_door},
		{9, 22, 3, 1, NULL, false, false, SceneDimigo_on_door},
		{37, 0, 1, 22, NULL, false, false, SceneDimigo_on_ujunghaksa}
	};

	scene_dimigo_struct_cnt = 13;
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
	else if (ret == RETURNVAL_EARTHQUAKE_MISSION)
	{
		Game_print_earthquake(1000);

		Game_speechbubble("와! 지진이 멈췄다!");
		
		Game_system_message("퀘스트 완료 : 지진 발생");
		quest_progress_bongwan = 10;

		if (SceneDimigo_check_end())
			SceneDimigo_clear();

		return;
	}
}

bool SceneDimigo_check_end()
{
	return quest_progress_bongwan == 10 && quest_progress_cafeteria == 11;
}

void SceneDimigo_clear()
{
	Sleep(1000);


	Game_ending_credit("당신은 디미고에서의 재난 상황에서 살아남았습니다.\n\n"
		"디미고에서 오늘 겪은 것과 비슷한 재난이 발생한다면\n\n"
		"지금 한것처럼 효과적으로 대처해 주세요.\n\n"
		"\n\n\n\n만든이들"
		"\n\n정현우"
		"\n\n이동현"
		"\n\n\n\n제작에 사용된 프로그램"
		"\nVisual Studio"
		"\nFigma" 
		"\n그림판"
		"\nGoldWave"
		"\nMicrosoft Edge"
		"\n스마터치"
		"\nSafari"
		"\nMicrosoft Remote Desktop"
		"\n파일 탐색기"
		"\nFirefox"
		"\n배달의민족"
		"\nFirefox Developer Edition"
		"\nChrome"
		"\nWhale"
		"\nNaver Pay"
		"\nCloudMounter"
		"\nDiscord"
		"\nKakao T"
		"\n일레클"
		"\nGithub Desktop"
		"\nBudDot"
		"\n코레일톡"
		"\n토스"
		"\n\n\n\n제작에 사용된 장비"
		"\nIntel NUC i5"
		"\nMacBook Pro 14"
		"\nHP 250 G7"
		"\nLG UltraGear 15.6"
		"\niPhone 14 Pro"
		"\nKTX-1"
		"\niPhone 13 Mini"
		"\nSamdasoo"
		"\nLG V50 ThinQ"
		"\niPad Mini 5"
		"\niPad Mini 6"
		"\nApple Pencil (1st generation)"
		"\nApple Pencil (2nd generation)"
		"\nAirPods Pro"
		"\nAirPods"
		"\nMX Keys Mini"
		"\nMX Master 3"
		"\nAnker MagSafe Battery"
		"\nDaiso Multi Tab (2.5m)"
		"\nEarPods"
		"\nLogitech G102"
		"\nipTIME U1000Plus"
		"\n구론산바몬드"
		"\nPolishing Cloth"
		"\niPhone 74 Air"
		"\nUSB-C Charge Cable (1m)"
		"\nUSB-C to MagSafe 3 Cable (2m)"
		"\n67W USB-C Power Adapter"


		"\n\n\n\n클리어를 축하드립니다!");

	Game_clear();

	char str[2][100] = {
		"끝내기",
		"디미고 탐방하기"
	};

	int res = Game_modal_select_box_speech("모든 재난 상황에서 탈출했어! 게임을 끝낼까?", str, 2);

	if (res == 0)
	{
		Game_reset_all();
		return;
	}
	else if (res == 1)
	{
		Game_print_map(true);
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
	if (ch == 'a')
	{
		SceneDimigo_clear();
	}

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
			Game_system_message("화재 진압에 성공했습니다.");
			Game_speechbubble("소방관을 도와 불을 끄는데 성공했어!");
			Game_speechbubble("너무 보람찬 하루인 것 같아.");

			Game_system_message("퀘스트 완료: 급식실 화재");

			quest_progress_cafeteria = 11;

			if (SceneDimigo_check_end())
				SceneDimigo_clear();
		}
	}
}

int outside_time = 0;

// 50ms마다 호출됨
void SceneDimigo_on_tick()
{
	if (quest_progress_cafeteria == 10)
	{
		cafeteria_health++;
		SceneDimigo_change_cafeteria_skin();

		if (cafeteria_health > 100)
		{
			scene_dimigo_structure[1].bitmap = bitmap_bongwan[5][0];
			scene_dimigo_structure[2].bitmap = bitmap_bongwan[5][1];

			Game_print_map(false);

			Game_speechbubble("이런! 디미고가 전소되었어.");
			Game_die();
			return;
		}

		Game_print_map(false);
	}

	if (outside_time <= 300000 && (quest_progress_cafeteria == 0 || quest_progress_cafeteria == 11))
	{
		outside_time += 50;

		if (outside_time == 60000)
		{
			Game_speechbubble("바깥에 너무 오래 있었다.");

			char oong[2][100] = {
			"미세먼지인가 봐!",
			"하늘이 내린 저주야!",

			//답변
			};
			if (Game_modal_select_box_speech("콜록콜록! 켁켁! 숨이 안 쉬어져.", oong, 2) == 1)
			{
				Game_speechbubble("신이 노하셨다!! 우어억!!");
				Game_print_earthquake(1000);

				Game_die();
				return;
			}
			else {
				char ooong[2][100] = {
					"내 코가 필터다!! 마스크따윈 필요 없어!",
					"KF94 마스크를 쓰자!",

					//답변
				};
				if (Game_modal_select_box_speech("마스크를 써야 할 것 같아..", ooong, 2) == 1)
				{
					Game_speechbubble("휴, 살았다.\n\n미세먼지를 피해 본관 안으로 들어가보자.");
					quest_progress_bongwan = 1;
				}
				else {
					Game_speechbubble("켁켁! 숨이 안 쉬어져!");
					Game_system_message("미세먼지 농도가 높은 곳에서 오래 노출되는 경우 \n\n심혈관질환, 호흡기질환, 폐암 등에 걸릴 수 있습니다.");


					Game_die();
					return;

				}
			}
			return;
		}
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
			Game_speechbubble("앗! 뜨거워!");
			Game_system_message("화재 현장에 다시 들어가는 것은 매우 위험한 행동입니다.");


			Game_die();
			return;
		}

		//image_layer.fadeOut(&image_layer, NULL);
		//Sleep(1000);

		Game_change_scene(SceneCafeteria_load(), true);
	}
}

void SceneDimigo_on_bongwan_clear(int st, int dir)
{
	char oong[2][100] = {
		"들어가자!",
		"아니야, 안 갈래."
	};

	if (Game_modal_select_box_speech("본관에 들어갈까?", oong, 2) == 0)
	{
		Game_change_scene(SceneBongwan_load(), true);
	}
	else {

		Game_speechbubble("켁켁! 숨이 안 쉬어져!");
		Game_system_message("미세먼지 농도가 높은 곳에서 오래 노출되는 경우 \n\n심혈관질환, 호흡기질환, 폐암 등에 걸릴 수 있습니다.");

		Game_die();
		return;
	}
}

void SceneDimigo_on_bongwan(int st, int dir)
{
	if (dir != UP)
		return;

	if (quest_progress_bongwan == 1)
	{
		SceneDimigo_on_bongwan_clear(st, dir);
		return;
	}

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
	
	char str[2][100] = {
		"들어가보자!",
		"돌아가자."
	};

	if (Game_modal_select_box_speech("학봉관에 들어갈까?", str, 2) == 0)
	{
		Game_change_scene(SceneHakbonggwan_load(), true);
	}
}
//
void SceneDimigo_on_door(int st, int dir)
{
	Game_speechbubble("학교 밖으로 나가면 안 될 것 같아!");
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
		char str[2][100] = {
			"들어가보자!",
			"돌아가자."
		};

		if (Game_modal_select_box_speech("신관에 들어갈까?", str, 2) == 0)
		{
			Game_change_scene(SceneSingwan_load(), true);
		}
		return;
	}
	else if (dir == LEFT)
	{
		Game_speechbubble("엇, 여기는 매점인가 봐! 아쉽지만 닫혀 있네.");
	}
}

void SceneDimigo_on_structure_active(int st, int dir)
{
	//if (dir != UP)
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

	outside_time = 0;
}