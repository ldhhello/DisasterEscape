// Scene: 게임의 장면을 나타내는 인터페이스
// 게임의 모든 장면은 Scene으로 추상화되어 작동한다!

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
	void (*on_tick)();

	int scene_id;

	const char* background_music; // NULL이면 기본값!

	void (*on_load)(); // 내가 지금 파일로 로드됐을때 호출됨! (처음 1번)
	// on_load는 
} Scene;