#define _CRT_SECURE_NO_WARNINGS
#include "Music.h"

#pragma comment(lib, "winmm.lib")

const char* music_background;

// 음악을 플레이한다!
void Music_play(const char* music)
{
	/*char command[100];
	sprintf(command, "play %s", music);
	mciSendString(command, NULL, 0, NULL);*/
	PlaySound(music, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC);
}

// 음악을 멈춘다!
void Music_stop(const char* music)
{
	/*char command[100];
	sprintf(command, "stop %s", music);
	mciSendString(command, NULL, 0, NULL);*/
	PlaySound(0, 0, 0);
}

// 음악을 배경음으로 플레이한다(연속 재생)
void Music_set_background(const char* music)
{
	/*if (music_background != NULL)
		Music_stop(music);

	music_background = music;
	Music_play(music);*/

	PlaySound(music, GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_LOOP);
}

// 음악 배경음을 멈춘다 (사실 구현은 Music_stop이랑 같다)
void Music_stop_background()
{
	PlaySound(0, 0, 0);
}