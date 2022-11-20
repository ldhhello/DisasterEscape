#pragma once

#include "Include.h"
#include "Scene.h"

// 얘는 게임 전체에 대한 정보를 가지고 있음
// 예를들어 이사람이 어떤 스테이지를 깼는지, 등등...
typedef struct
{
	int last_stage;

	int x, y;
} Game;

extern void Game_print_map(bool fade_in);

extern void Game_change_scene(Scene sc, bool is_enter);

extern void Game_speechbubble(const char* str);
extern int Game_modal_select_box(char(*str)[100], int cnt);
extern int Game_modal_select_box_speech(char* speech, char(*str)[100], int cnt);

extern void Game_modal();