#include <stdio.h>
#include "Include.h"
#include "StartWindow.h"

HWND hWnd;
ImageLayer image_layer;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

HBITMAP bitmap_start_screen;
HBITMAP bitmap_loading_image;
HBITMAP bitmap_speech_bubble;

void clear_cursor()
{
	CONSOLE_CURSOR_INFO cc;
	cc.bVisible = FALSE;
	cc.dwSize = 1;
	SetConsoleCursorInfo
	(GetStdHandle(STD_OUTPUT_HANDLE),
		&cc);
}

void load_image()
{
	bitmap_start_screen = (HBITMAP)LoadImage(NULL, "D:\\test3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_loading_image = (HBITMAP)LoadImage(NULL, "D:\\loading.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_speech_bubble = (HBITMAP)LoadImage(NULL, "D:\\speechbubble.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void initialize()
{
	load_image();

	hWnd = GetConsoleWindow();
	image_layer = DEFAULT_IMAGE_LAYER;
	image_layer.transparentColor = RGB(29, 222, 38);

	image_layer.initialize(&image_layer);
}

void initialize_screen()
{
	//SetWindowPos(hWnd, HWND_TOP, 0, 0, 1366, 768, SWP_NOMOVE);
	system("mode con cols=180 lines=48");
	clear_cursor();

	Sleep(500);
}

int main()
{
	initialize();
	initialize_screen();

	StartWindow_modal();

	return 0;
}