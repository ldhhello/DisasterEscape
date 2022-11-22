#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
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
extern void Rectangle_(HDC hdc, int left, int top, int right, int bottom);
extern int getTextWidth(HDC hdc, char* fontName, int size, char* text);
extern int next_start_pos(int prev, int cursor, int screen_size, int max_pos);

typedef char bool;
//const static bool false = 0;
//const static bool true = 1;

#define false 0
#define true 1

// on main.c
extern HBITMAP bitmap_start_screen;
extern HBITMAP bitmap_loading_image;
extern HBITMAP bitmap_loading_none;
extern HBITMAP bitmap_speech_bubble;
extern HBITMAP bitmap_player[4];
extern HBITMAP bitmap_house;
extern HBITMAP bitmap_hakbonggwan;
extern HBITMAP bitmap_singwan;
extern HBITMAP bitmap_cafeteria;
extern HBITMAP bitmap_system_msg;
extern HBITMAP bitmap_youdie;

extern HBITMAP bitmap_bongwan1;
extern HBITMAP bitmap_bongwan2;

extern HBITMAP bitmap_bongwan[6][2];

extern HBITMAP bitmap_tile[20]; // ¸Ê ¹Ù´Ú Å¸ÀÏ

extern HBITMAP bitmap_button[3][2];

extern HBITMAP bitmap_gameinfo;
extern HBITMAP bitmap_water;

extern HBITMAP bitmap_naoh;
extern HBITMAP bitmap_towel;
extern HBITMAP bitmap_bibimbap;

extern HBITMAP bitmap_arrow;
extern HBITMAP bitmap_clear;

const static int SCREEN_X = 180;
const static int SCREEN_Y = 96;

#define RETURNVAL_CAFETERIA_MISSION 1