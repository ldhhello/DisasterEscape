#pragma once

#include "Include.h"

// ��� ���� ��ü�� ���� ������ ������ ����
// ������� �̻���� � ���������� ������, ���...
typedef struct
{
	int last_stage;

	int x, y;
} Game;

extern void Game_modal();