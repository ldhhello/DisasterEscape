#pragma once

#include "Include.h"

// 얘는 게임 전체에 대한 정보를 가지고 있음
// 예를들어 이사람이 어떤 스테이지를 깼는지, 등등...
typedef struct
{
	char ch;
} Game;

extern void Game_modal();