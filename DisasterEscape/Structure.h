// Structure 객체: 게임에 있는 구조물을 나타내는 클래스!

#pragma once
#include "Include.h"

typedef struct
{
	int x, y; // 이미지의 x, y좌표
	int width, height; // 이미지의 가로, 세로 크기
	
	HBITMAP bitmap; // 띄울 이미지

	bool is_hide; // 유령 여부. 이게 true면 유령이 되어 보이지도 않고 상호작용하지도 않는다
	bool passable; // 배경 여부. 이게 true면 보이지만 상호작용하지 않는다

	void (*on_active)(int st, int dir); // 상호작용 시 호출되는 함수. 이게 NULL이면 기본값 (Scene에 정의되는) 이 호출된다

	double scale; // 이미지 스케일 (안채우면 ImageLayer의 기본값 16을 따른다)

} Structure;