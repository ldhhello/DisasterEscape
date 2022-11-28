// 게임에 들어가는 음악을 전부 관리하는 코드이다
// 이 시스템 전체의 음악은 모두 이곳에서 관리된다!
// 음악 동시에 출력하는 상황이 없어서 여기서는 모두 PlaySound를 통해 음악을 처리한다!
// 여기서 처리하는 모든 음악은 리소스에서 읽어오는데 MAKEINTRESOURCE(리소스 이름) 을 인자로 넘겨주면 된다!

#pragma once

#include "Include.h"

extern void Music_play(const char* music);
extern void Music_stop(const char* music);
extern void Music_set_background(const char* music);
extern void Music_stop_background();