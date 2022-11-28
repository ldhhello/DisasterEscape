// Scene: ������ ����� ��Ÿ���� �������̽�
// ������ ��� ����� Scene���� �߻�ȭ�Ǿ� 

#pragma once

#include "Include.h"
#include "Structure.h"

typedef struct
{
	int** (*load_map)(int* x, int* y);
	Structure* (*load_structure)(int* sz);
	void (*on_structure_active)(int st, int dir);
	void (*on_start)();
	void (*on_return)(int ret); // �ٸ� ������ ��ȯ�Ǿ� ���ƿ��� �� ȣ���

	int start_x, start_y;

	bool fixed_map;

	void (*on_key_pressed)(char ch);
	void (*on_tick)();

	int scene_id;
} Scene;