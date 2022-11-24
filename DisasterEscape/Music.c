#define _CRT_SECURE_NO_WARNINGS
#include "Music.h"

#pragma comment(lib, "winmm.lib")

const char* music_background;

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

void Music_set_background(const char* music)
{
	if (music_background != NULL)
		Music_stop(music);

	music_background = music;
	Music_play(music);
}