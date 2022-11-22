#include "SceneDimigo.h"
#include "Game.h"

#include "SceneCafeteria.h"

#include "SceneBongwan.h"

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
		// ���� ��Ÿ�� �̹��� 1
		//scene_dimigo_structure[1].bitmap = bitmap_bongwan[4][0];
		//scene_dimigo_structure[2].bitmap = bitmap_bongwan[4][1];
		cafeteria_health = 50;
		SceneDimigo_change_cafeteria_skin();
		Game_print_map(false);

		Game_speechbubble("��.. ������ ���Դ�. �ϸ��͸� ���� ���߾�.");
		Game_speechbubble("�ҹ���� ���� ���� ������!\n\n[N]Ű�� ������ ���� �߻��� �� �־�.");
		quest_progress_cafeteria = 10;
		return;
	}
}

void SceneDimigo_on_start()
{
	if (!is_first_dimigo)
		return;

	is_first_dimigo = false;

	Game_speechbubble("���� 1�г� 7�� ���õ.");
	Game_speechbubble("���� �б��� �����ؼ� ���� �ƹ��͵� �𸣰ڴ�.");
	Game_speechbubble("�б��� Ž���غ��鼭 �б��� ���ؼ� �������߰ڱ�!");
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
		//Game_speechbubble("���� ���� ���� ������ ���� ��ư�̴�!");

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
			Game_system_message("ȭ�� ���п� �����߽��ϴ�.");
			Game_speechbubble("�ҹ���� ���� ���� ���µ� �����߾�!");
			Game_speechbubble("�ʹ� ������ �Ϸ��� �� ����.");

			Game_system_message("����Ʈ �Ϸ�: �޽Ľ� ȭ��");

			quest_progress_cafeteria = 11;

			char oong[2][100] = {
			"�̼������ΰ� ��!",
			"�ϴ��� ���� ���־�!",
			
			//�亯
			};
			if (Game_modal_select_box_speech("�ݷ��ݷ�! ����! ���� �� ������.", oong, 2) == 1)
			{
				Game_speechbubble("���� ���ϼ̴�!! ����!!");
				Game_print_earthquake(1000);

				Game_die();
				return;
			}
			else {
				char ooong[2][100] = {
					"�� �ڰ� ���ʹ�!! ����ũ���� �ʿ� ����!",
					"KF94 ����ũ�� ����!",

					//�亯
				};
				if (Game_modal_select_box_speech("����ũ�� ��� �� �� ����..", ooong, 2) == 1)
				{
					Game_speechbubble("��, ��Ҵ�.\n\n�̼������� ���� ���� ������ ������.");
					quest_progress_bongwan = 1;
				}
				else {
					Game_speechbubble("����! ���� �� ������!");
					Game_system_message("�̼����� �󵵰� ���� ������ ���� ����Ǵ� ��� \n\n��������ȯ, ȣ�����ȯ, ��� � �ɸ� �� �ֽ��ϴ�.");

					
					Game_die();
					return;

				}
			}

			
		}
	}
}

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

			Game_speechbubble("�̷�! ��̰� ���ҵǾ���.");
			Game_die();
			return;
		}

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

	char str[2][100] = { "������!","�ƴϾ�, �� ����."};

	if (Game_modal_select_box_speech("���ִ� ������ ����!\n\n�޽Ľǿ� ������?", str, 2) == 0)
	{
		if (quest_progress_cafeteria == 10)
		{
			Game_speechbubble("��! �߰ſ�!");
			Game_system_message("ȭ�� ���忡 �ٽ� ���� ���� �ſ� ������ �ൿ�Դϴ�.");


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
		"����!",
		"�ƴϾ�, �� ����."
	};

	if (Game_modal_select_box_speech("������ ����?", oong, 2) == 0)
	{
		Game_change_scene(SceneBongwan_load(), true);
	}
	else {

		Game_speechbubble("����! ���� �� ������!");
		Game_system_message("�̼����� �󵵰� ���� ������ ���� ����Ǵ� ��� \n\n��������ȯ, ȣ�����ȯ, ��� � �ɸ� �� �ֽ��ϴ�.");

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

	Game_speechbubble("��, �� �ǹ��� ��̰� �����ΰ���!");
	char oong[2][100] = {
		"����� ���� �ƴѵ�, ���� �νð� ����?",
		"���� ����.",
		//�亯
	};
	if (Game_modal_select_box_speech("�� ����?", oong, 2) == 0)
	{
		Game_speechbubble("����!!!!!");
		Game_print_earthquake(1000);
		Game_system_message("���� �����ϸ� �ɰ��� �λ��� ���� �� �ֽ��ϴ�.");
		Game_die();
		return;
	}
	else {
		char oong[3][100] = {
		"������ ���� �����!",
		"�谡 ���� �� ����. ���� ���ư��߰ھ�.",
		"�ƴϾ�. ���� ����"
		//�亯
		};
		if (Game_modal_select_box_speech("�׷��� ����� �� ����. �ٽ� �ѹ� �����غ���!", oong, 3) == 0)
		{
			Game_speechbubble("����!!!!!");
			Game_print_earthquake(1000);
			Game_system_message("���� �����ϸ� �ɰ��� �λ��� ���� �� �ֽ��ϴ�.");
			Game_die();
			return;
		}
		else {
			Game_speechbubble("��Ҵ�.");
			
		}
	}
}

void SceneDimigo_on_hakbonggwan(int st, int dir)
{
	if (dir != LEFT)
		return;

	Game_speechbubble("����� �츮���� �����ڸ� �к����̱�!");
	Game_system_message("�������� ���̱⵵ �ϴ�");
}

void SceneDimigo_on_door(int st, int dir)
{
	Game_speechbubble("�б� ������ ������ �� �ɰ� ����!");
	Game_ending_credit("���� ũ���� �׽�Ʈ!!\n\n"
		"ssib.al ������ ��� - ������\n\n"
		"���� �ִ� �� - ���ǰ��\n\n"
		"���� �ϰ� �ִ� �� - ����\n\n"
		"\n\n\n\n�����մϴ�!"
		"\n���縵 �����~!!~@!~"
		"\n��  ���� �ƽô±���!!@#!@#!@#!@##"
		"\n�̳� ��ƽ��ϴ�!"
		"\nå�� ������ �̵��ϼ���`~~!~!");

	Game_clear();
}

void SceneDimigo_on_ujunghaksa(int st, int dir)
{ 
	char str[2][100] = { "������!","������ �� ����. ���ư���." };

	if (Game_modal_select_box_speech("���� �ָ��� ����� �����ִ� ����?\n\n��.. ���� ������?", str, 2) == 0)
	{
		Game_system_message("�������� ��ҿ� ���� ���� �ſ� ������ �ൿ�Դϴ�.");
		Game_die();
	}
}

void SceneDimigo_on_singwan(int st, int dir)
{
	if (dir == UP)
	{
		Game_speechbubble("�� �ǹ��� 3�г���� �ִ� �Ű��̱���!");
		return;
	}
	else if (dir == LEFT)
	{
		Game_speechbubble("��, ����� �����ΰ� ��! �ƽ����� ���� �ֳ�.");
	}
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
		Game_print_map(false);
		Sleep(1000);

		Game_speechbubble("���� ��ƸԾ���!!");

		break;
	case 3:
		Game_speechbubble("���� ����Ѵٰ�??? �� ����� ��� �ϴ� �Ŵ�??");
		break;
	}
}

// �װų� ����� ������ ������ �����Ҷ� ȣ��Ǵ� �ڵ�
void SceneDimigo_reset()
{
	struct_loaded_dimigo = false;
	is_first_dimigo = true;
}