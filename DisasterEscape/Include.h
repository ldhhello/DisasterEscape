// ��ü �ý��ۿ� �ʿ��� �Լ� / ���� / define ���� ��Ƴ��� ����!
// ��ü �ý����̶� ���� ���� ���ư��� �ڵ� (ImageLayer�� SaveFile ���� �͵�..) �� �ƴϸ� �� ������ include �ؾ� �Ѵ�

#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "ImageLayer.h"

#include "resource.h"

// on main.c
extern HWND hWnd;
extern ImageLayer image_layer;

#define LEFT 75
#define RIGHT 77
#define DOWN 80
#define UP 72
#define SPACE 32

// on Utils.c
extern void printTextWithAngle(HDC hdc, int x, int y, char* fontName, int size, int weight, int angle, COLORREF textColor, int align, char* text);
extern void printText(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, const char* text);
extern void printTextW(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, const char* text);
extern void Rectangle_(HDC hdc, int left, int top, int right, int bottom);
extern int getTextWidth(HDC hdc, char* fontName, int size, char* text);
extern int next_start_pos(int prev, int cursor, int screen_size, int max_pos);
extern int sleep_(int ms);

// on main.c
extern HBITMAP bitmap_start_screen;
extern HBITMAP bitmap_loading_image;
extern HBITMAP bitmap_loading_none;
extern HBITMAP bitmap_speech_bubble;
extern HBITMAP bitmap_speech_bubble_ldh;
extern HBITMAP bitmap_speech_bubble_ziaoming;
extern HBITMAP bitmap_player[4];
extern HBITMAP bitmap_house;
extern HBITMAP bitmap_hakbonggwan;
extern HBITMAP bitmap_singwan[6];
extern HBITMAP bitmap_cafeteria;
extern HBITMAP bitmap_system_msg;
extern HBITMAP bitmap_youdie;

extern HBITMAP bitmap_bongwan1;
extern HBITMAP bitmap_bongwan2;

extern HBITMAP bitmap_bongwan[6][2];

extern HBITMAP bitmap_tile[20]; // �� �ٴ� Ÿ��

extern HBITMAP bitmap_button[3][2];

extern HBITMAP bitmap_gameinfo;
extern HBITMAP bitmap_water;

extern HBITMAP bitmap_naoh;
extern HBITMAP bitmap_towel;
extern HBITMAP bitmap_bibimbap;

extern HBITMAP bitmap_arrow;
extern HBITMAP bitmap_clear;

extern HBITMAP bitmap_bongwan_inside;

extern HBITMAP bitmap_puricare;

extern HBITMAP bitmap_hakbonggwan_inside;
extern HBITMAP bitmap_singwan_inside;
extern HBITMAP bitmap_gangdang_inside;

extern HBITMAP bitmap_gangdang;
extern HBITMAP bitmap_healthjang;
extern HBITMAP bitmap_biggangdang;

extern HBITMAP bitmap_save;
extern HBITMAP bitmap_game_load;

extern HBITMAP bitmap_kf94;

extern HBITMAP bitmap_donghyun;
extern HBITMAP bitmap_ziaoming;

extern HBITMAP bitmap_fire;

extern HBITMAP bitmap_maejom_inside;
extern HBITMAP bitmap_maejom_dark;

extern TCHAR appdata_path[MAX_PATH];
extern TCHAR save_path[MAX_PATH];

const static int SCREEN_X = 180;
const static int SCREEN_Y = 96;

// Game_set_return(), Scene::on_return() �� ����
#define RETURNVAL_CAFETERIA_MISSION 1
#define RETURNVAL_EARTHQUAKE_MISSION 2
#define RETURNVAL_MAEJOM_MISSION 3

// Scene::scene_id, Game�� �ִ� ���� ������.. ���� ����
#define SCENE_DIMIGO 1
#define SCENE_CAFETERIA 2
#define SCENE_BONGWAN 3
#define SCENE_GANGDANG 4
#define SCENE_HEALTHJANG 5
#define SCENE_SINGWAN 6
#define SCENE_BIGGANGDANG 7
#define SCENE_HAKBONGGWAN 8
#define SCENE_MAEJOM 9

static const char* ending_credit_str = "����� ��̰����� �糭 ��Ȳ���� ��Ƴ��ҽ��ϴ�.\n\n"
"��̰��� ���� ���� �Ͱ� ����� �糭�� �߻��Ѵٸ�\n\n"
"���� �Ѱ�ó�� ȿ�������� ��ó�� �ּ���.\n\n"
"\n\n\n\n�����̵�"
"\n\n������"
"\n\n�̵���"
"\n\n\n\n���ۿ� ���� ���α׷�"
"\nVisual Studio"
"\nFigma"
"\n�׸���"
"\nGoldWave"
"\nMicrosoft Edge"
"\n������ġ"
"\nSafari"
"\nMicrosoft Remote Desktop"
"\n���� Ž����"
"\nFirefox"
"\n����ǹ���"
"\nFirefox Developer Edition"
"\nChrome"
"\nWhale"
"\nNaver Pay"
"\nCloudMounter"
"\nDiscord"
"\nKakao T"
"\n�Ϸ�Ŭ"
"\nGithub Desktop"
"\nBudDot"
"\n�ڷ�����"
"\n�佺"
"\n\n\n\n���ۿ� ���� ���"
"\nIntel NUC i5"
"\nMacBook Pro 14"
"\nHP 250 G7"
"\nLG UltraGear 15.6"
"\niPhone 14 Pro"
"\nKTX-1"
"\niPhone 13 Mini"
"\nSamdasoo"
"\nLG V50 ThinQ"
"\niPad Mini 5"
"\niPad Mini 6"
"\nApple Pencil (1st generation)"
"\nApple Pencil (2nd generation)"
"\nAirPods Pro"
"\nAirPods"
"\nMX Keys Mini"
"\nMX Master 3"
"\nAnker MagSafe Battery"
"\nDaiso Multi Tab (2.5m)"
"\nEarPods"
"\nLogitech G102"
"\nipTIME U1000Plus"
"\n���л�ٸ��"
"\nPolishing Cloth"
"\niPhone 74 Air"
"\nUSB-C Charge Cable (1m)"
"\nUSB-C to MagSafe 3 Cable (2m)"
"\n67W USB-C Power Adapter"


"\n\n\n\nŬ��� ���ϵ帳�ϴ�!";