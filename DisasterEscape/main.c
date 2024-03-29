#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "Include.h"
#include "StartWindow.h"
#include "Music.h"

#include <shlobj_core.h>

//#include <gdiplusflat.h>

//#pragma comment(lib, "gdiplus.lib")
//
//struct GdiplusStartupInput {
//	UINT32         GdiplusVersion;
//	void* DebugEventCallback;
//	BOOL           SuppressBackgroundThread;
//	BOOL           SuppressExternalCodecs;
//};
//
//struct GdiplusStartupOutput {
//	void *a, *b;
//};
//
//extern int __stdcall
//GdipCreateBitmapFromFile(const char* filename, void** image);
//
//extern int GdiplusStartup(ULONG_PTR* token, const void* input, void* output);
//
//extern int GdipCreateHBITMAPFromBitmap(void* image, HBITMAP* hbitmap, int background);
//
//extern int GdipCreateBitmapFromResource(HINSTANCE hInstance, const char* lpBitmapName, void** image);

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
HBITMAP bitmap_speech_bubble_ldh;
HBITMAP bitmap_speech_bubble_ziaoming;
HBITMAP bitmap_jandi;
HBITMAP bitmap_player[4]; // 플레이어 (0 1 2 3 은 4개 방향임)
HBITMAP bitmap_house; // 집 테스트
HBITMAP bitmap_hakbonggwan;
HBITMAP bitmap_bongwan1;
HBITMAP bitmap_bongwan2;
HBITMAP bitmap_singwan[6]; // 0으로갈수록 불이 안난거, 5로갈수록 불이 많이난거
HBITMAP bitmap_cafeteria;
HBITMAP bitmap_youdie;

HBITMAP bitmap_bongwan[6][2]; // 첫번째 인자: 0으로갈수록 불이 안난거, 5로갈수록 불이 많이난거 두번째인자: bongwan1인지 2인지 (왼쪽 절반, 오른쪽 절반)

HBITMAP bitmap_system_msg;

HBITMAP bitmap_pngtest;

HBITMAP bitmap_tile[20]; // 맵 바닥 타일
HBITMAP bitmap_button[3][2]; // [버튼 종류][활성 여부]

HBITMAP bitmap_gameinfo;
HBITMAP bitmap_water;

HBITMAP bitmap_naoh;
HBITMAP bitmap_towel;
HBITMAP bitmap_bibimbap;

HBITMAP bitmap_arrow;
HBITMAP bitmap_clear;

HBITMAP bitmap_bongwan_inside;

HBITMAP bitmap_puricare;

HBITMAP bitmap_hakbonggwan_inside;
HBITMAP bitmap_singwan_inside;
HBITMAP bitmap_gangdang_inside;

HBITMAP bitmap_gangdang;
HBITMAP bitmap_healthjang;
HBITMAP bitmap_biggangdang;

HBITMAP bitmap_save;
HBITMAP bitmap_game_load;

HBITMAP bitmap_kf94;

HBITMAP bitmap_donghyun;
HBITMAP bitmap_ziaoming;

HBITMAP bitmap_fire;

HBITMAP bitmap_maejom_inside;
HBITMAP bitmap_maejom_dark;

HBITMAP bitmap_skip;

HBITMAP bitmap_dimigang;
HBITMAP bitmap_aloe;

TCHAR appdata_path[MAX_PATH];
TCHAR save_path[MAX_PATH];

// 커서 지우는 함수
void clear_cursor()
{
	CONSOLE_CURSOR_INFO cc;
	cc.bVisible = FALSE;
	cc.dwSize = 1;
	if (!SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cc))
	{
		printf("Error: Failed to hide console cursor!!");
		exit(0);
	}
}

// 비트맵 로딩하는 함수
void load_image()
{
	bitmap_start_screen = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MAINSCREEN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_loading_image = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOADING), IMAGE_BITMAP, 0, 0, 0);
	bitmap_loading_none = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOADING_NONE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_speech_bubble = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MESSAGEBOX), IMAGE_BITMAP, 0, 0, 0);
	bitmap_speech_bubble_ldh = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SPEECHBUBBLE_LDH), IMAGE_BITMAP, 0, 0, 0);
	bitmap_speech_bubble_ziaoming = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SPEECHBUBBLE_ZIAOMING), IMAGE_BITMAP, 0, 0, 0);

	bitmap_tile[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_JANDI), IMAGE_BITMAP, 0, 0, 0);
	bitmap_tile[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PATH), IMAGE_BITMAP, 0, 0, 0);

	//bitmap_player = (HBITMAP)LoadImage(NULL, "D:\\player.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_player[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAYER_UP), IMAGE_BITMAP, 0, 0, 0);
	bitmap_player[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAYER_DOWN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_player[2] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAYER_LEFT), IMAGE_BITMAP, 0, 0, 0);
	bitmap_player[3] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PLAYER_RIGHT), IMAGE_BITMAP, 0, 0, 0);

	//bitmap_house = (HBITMAP)LoadImage(NULL, "D:\\house.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	bitmap_house = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_HOUSE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_hakbonggwan = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_HAKBONGGWAN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan1 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan2 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_cafeteria = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_CAFETERIA), IMAGE_BITMAP, 0, 0, 0);

	bitmap_singwan[0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan[1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_FIRE1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan[2] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_FIRE2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan[3] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_FIRE3), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan[4] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_FIRE4), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan[5] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_FIRE5), IMAGE_BITMAP, 0, 0, 0);

	//bitmap_system_msg = (HBITMAP)LoadImage(NULL, "D:\\system-msg.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

	bitmap_youdie = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_YOUDIE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_button[0][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[0][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_START_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[1][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_LOAD_ACTIVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO), IMAGE_BITMAP, 0, 0, 0);
	bitmap_button[2][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAMEINFO_ACTIVE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_gameinfo = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_GAMEINFO_SCREEN), IMAGE_BITMAP, 0, 0, 0);

	bitmap_bongwan[0][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[0][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[1][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE1_1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[1][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE1_2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[2][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE2_1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[2][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE2_2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[3][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE3_1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[3][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE3_2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[4][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE4_1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[4][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE4_2), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[5][0] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE5_1), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bongwan[5][1] = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_FIRE5_2), IMAGE_BITMAP, 0, 0, 0);


	bitmap_water = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_WATER), IMAGE_BITMAP, 0, 0, 0);
	bitmap_naoh = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_NaOH), IMAGE_BITMAP, 0, 0, 0);
	bitmap_towel = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_TOWEL), IMAGE_BITMAP, 0, 0, 0);
	bitmap_bibimbap = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BIBIMBAP), IMAGE_BITMAP, 0, 0, 0);

	bitmap_arrow = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_ARROW), IMAGE_BITMAP, 0, 0, 0);
	bitmap_clear = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_CLEAR), IMAGE_BITMAP, 0, 0, 0);

	bitmap_bongwan_inside = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BONGWAN_INSIDE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_puricare = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_PURICARE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_hakbonggwan_inside = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_HAKBONGGWAN_INSIDE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_singwan_inside = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SINGWAN_INSIDE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_gangdang_inside = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GANGDANG_INSIDE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_gangdang = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_UNDONGJANG), IMAGE_BITMAP, 0, 0, 0);
	bitmap_healthjang = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_HEALTHJANG), IMAGE_BITMAP, 0, 0, 0);
	bitmap_biggangdang = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_BIGGANGDANG), IMAGE_BITMAP, 0, 0, 0);

	bitmap_save = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SAVE), IMAGE_BITMAP, 0, 0, 0);
	bitmap_game_load = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_GAME_LOAD), IMAGE_BITMAP, 0, 0, 0);

	bitmap_kf94 = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_KF94), IMAGE_BITMAP, 0, 0, 0);

	bitmap_donghyun = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_DONGHYUN), IMAGE_BITMAP, 0, 0, 0);
	bitmap_ziaoming = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_ZIAOMING), IMAGE_BITMAP, 0, 0, 0);

	bitmap_fire = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_FIRE), IMAGE_BITMAP, 0, 0, 0);

	bitmap_maejom_inside = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MAEJOM), IMAGE_BITMAP, 0, 0, 0);
	bitmap_maejom_dark = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_MAEJOM_DARK), IMAGE_BITMAP, 0, 0, 0);

	bitmap_skip = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_SKIP), IMAGE_BITMAP, 0, 0, 0);

	bitmap_dimigang = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_DIMIGANG), IMAGE_BITMAP, 0, 0, 0);
	bitmap_aloe = (HBITMAP)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP_ALOE), IMAGE_BITMAP, 0, 0, 0);

	//ULONG_PTR gp_token;
	//struct GdiplusStartupInput gpsi;
	//memset(&gpsi, 0, sizeof(struct GdiplusStartupInput));
	//gpsi.GdiplusVersion = 1;

	//int res1 = GdiplusStartup(&gp_token, &gpsi, NULL);

	//void* bitmap = NULL;
	//int res2 = GdipCreateBitmapFromResource(GetModuleHandle(NULL), MAKEINTRESOURCEA(IDB_BITMAP_GAMEINFO), &bitmap);
	////GdipCreateBitmapFromFile(L"D:\\bongwan.png", &bitmap);

	//int res3 = GdipCreateHBITMAPFromBitmap(bitmap, &bitmap_start_screen, 0xff000000);
}

// 전체 시스템 초기화
void initialize()
{
	load_image();

	hWnd = GetConsoleWindow();

	if (hWnd == NULL)
	{
		printf("Error: failed to get console handle!");
		exit(0);
	}

	image_layer = DEFAULT_IMAGE_LAYER;
	image_layer.transparentColor = RGB(29, 222, 38);

	image_layer.initialize(&image_layer);

	if (!SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, appdata_path)))
	{
		printf("Error: failed to load appdata path!!");
		exit(0);
	}

	sprintf(save_path, "%s\\DisasterEscape", appdata_path);

	if (CreateDirectory(save_path, NULL))
	{
		printf("Directory is not exist. Created new");
	}

	srand(time(NULL));
}

// 화면 초기화
void initialize_screen()
{
	system("title 재난 탈출 시뮬레이션");
	system("mode con cols=180 lines=48");
	clear_cursor();

	sleep_(500);
}

int main()
{
	//printf("DisasterEscape by LDH, JHU (KDMHS 21WP)\n");
	//printf("https://github.com/ldhhello\nhttps://github.com/budung");

	initialize();
	initialize_screen();

	StartWindow_modal();

	return 0;
}