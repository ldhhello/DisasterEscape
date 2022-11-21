#pragma once

#include "Include.h"
#include "Structure.h"

typedef struct
{
	int** (*load_map)(int* x, int* y);
	Structure* (*load_structure)(int* sz);
	void (*on_structure_active)(int st, int dir);
	void (*on_start)();
	void (*on_return)(int ret); // 다른 씬에서 반환되어 돌아왔을 때 호출됨

	int start_x, start_y;

	bool fixed_map;

	void (*on_key_pressed)(char ch);
} Scene;