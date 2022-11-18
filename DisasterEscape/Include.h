#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
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

extern void printTextWithAngle(HDC hdc, int x, int y, char* fontName, int size, int weight, int angle, COLORREF textColor, int align, char* text);
extern void printText(HDC hdc, int left, int top, int right, int bottom, char* fontName, int size, COLORREF textColor, int align, char* text);
extern void Rectangle_(HDC hdc, int left, int top, int right, int bottom);

typedef char bool;
const static bool false = 0;
const static bool true = 1;

// on main.c
extern HBITMAP bitmap_start_screen;
extern HBITMAP bitmap_loading_image;
extern HBITMAP bitmap_speech_bubble;
extern HBITMAP bitmap_jandi;
extern HBITMAP bitmap_player;
extern HBITMAP bitmap_house;

extern HBITMAP bitmap_button[3][2];

const static int SCREEN_X = 180;
const static int SCREEN_Y = 96;