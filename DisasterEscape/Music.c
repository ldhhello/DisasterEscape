#define _CRT_SECURE_NO_WARNINGS
#include "Music.h"

#pragma comment(lib, "winmm.lib")

void Music_play(const char* music)
{
	char command[100];
	sprintf(command, "play %s", music);
	mciSendString(command, NULL, 0, NULL);
}

void Music_stop(const char* music)
{
	char command[100];
	sprintf(command, "stop %s", music);
	mciSendString(command, NULL, 0, NULL);
}
