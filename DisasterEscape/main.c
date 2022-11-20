#include <stdio.h>
#include "Include.h"
#include "StartWindow.h"

//#include <gdiplusflat.h>

//#pragma comment(lib, "gdiplus.lib")
//
//struct GdiplusStartupInput {
//	UINT32         GdiplusVersion;
//	DebugEventProc DebugEventCallback;
//	BOOL           SuppressBackgroundThread;
//	BOOL           SuppressExternalCodecs;
//};

//extern int __stdcall
//GdipLoadImageFromFile(const char* filename, void** image);
//
//extern int GdiplusStartup(ULONG_PTR* token,
//
//	const void* input,
//
//	void* output);

HWND hWnd;
ImageLayer image_layer;

// extern in ImageLayerImpl.h

double RESOLUTION_MULTIPLIER = 1;

int WINDOW_WIDTH;
int WINDOW_HEIGHT;

HBITMAP bitmap_start_screen;
HBITMAP bitmap_loading_image;
HBITMAP bitmap_loading_none;
HBITMAP bitmap_speech_bubble;
HBITMAP bitmap_jandi; // 잔디 테스트
HBITMAP bitmap_player; // 플레이어 테스트
HBITMAP bitmap_house; // 집 테스트
HBITMAP bitmap_hakbonggwan;
HBITMAP bitmap_bongwan1;
HBITMAP bitmap_bongwan2;
HBITMAP bitmap_singwan;
HBITMAP bitmap_cafeteria;
HBITMAP bitmap_youdie;

HBITMAP bitmap_pngtest;

HBITMAP bitmap_tile[20]; // 맵 바닥 타일

HBITMAP bitmap_button[3][2]; // [버튼 종류][활성 여부]

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
	bitmap_start_screen = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MAINSCREEN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_loading_image = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOADING), IMAGE_BITMAP, 0, 0, 0);
	bitmap_loading_none = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOADING_NONE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_speech_bubble = (HBITMAP)LoadImage(NULL, "D:\\speechbubble.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap_tile[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_JANDI), IMAGE_BITMAP, 0, 0, 0);
	bitmap_tile[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PATH), IMAGE_BITMAP, 0, 0, 0);

	bitmap_player = (HBITMAP)LoadImage(NULL, "D:\\player.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_house = (HBITMAP)LoadImage(NULL, "D:\\house.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap_hakbonggwan = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_HAKBONGGWAN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan1 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_cafeteria = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_CAFETERIA), IMAGE_BITMAP, 0, 0, 0);

	bitmap_youdie = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_YOUDIE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_button[0][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[0][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO_ACTIVE), IMAGE_BITMAP, 0, 0, 0);

	/*void* image = NULL;
	int res = GdipLoadImageFromFile("D:\\bongwan.png", &image);*/
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