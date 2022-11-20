#pragma once
#include "Include.h"

typedef struct
{
	int x, y;
	int width, height;
	
	HBITMAP bitmap;

	bool is_hide;
	bool passable;

	void (*on_active)(int st, int dir);

	double scale;

} Structure;