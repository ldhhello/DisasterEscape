#pragma once

#include "Include.h"
#include "Structure.h"

typedef struct
{
	int** (*load_map)(int* x, int* y);
	Structure* (*load_structure)(int* sz);
	void (*on_structure_active)(int st, int dir);
} Scene;