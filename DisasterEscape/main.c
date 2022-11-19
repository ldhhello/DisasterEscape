#include <stdio.h>
#include "Include.h"
#include "StartWindow.h"

HWND hWnd;
ImageLayer image_layer;

// extern in ImageLayerImpl.h

double RESOLUTION_MULTIPLIER = 1;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

HBITMAP bitmap_start_screen;
HBITMAP bitmap_loading_image;
HBITMAP bitmap_speech_bubble;
HBITMAP bitmap_jandi; // �ܵ� �׽�Ʈ
HBITMAP bitmap_player; // �÷��̾� �׽�Ʈ
HBITMAP bitmap_house; // �� �׽�Ʈ

HBITMAP bitmap_tile[20]; // �� �ٴ� Ÿ��

HBITMAP bitmap_button[3][2]; // [��ư ����][Ȱ�� ����]

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
	//bitmap_start_screen = (HBITMAP)LoadImage(NULL, "D:\\test3.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_start_screen = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MAINSCREEN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_loading_image = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOADING), IMAGE_BITMAP, 0, 0, 0);
	bitmap_speech_bubble = (HBITMAP)LoadImage(NULL, "D:\\speechbubble.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap_tile[0] = bitmap_jandi = (HBITMAP)LoadImage(NULL, "D:\\jandi.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_tile[1] = (HBITMAP)LoadImage(NULL, "D:\\path.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap_player = (HBITMAP)LoadImage(NULL, "D:\\player.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_house = (HBITMAP)LoadImage(NULL, "D:\\house.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	

	// �ϴ� ��� �������� �׽�Ʈ�ϰ� ���ϸ�����..����
	bitmap_button[0][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[0][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO_ACTIVE), IMAGE_BITMAP, 0, 0, 0);

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