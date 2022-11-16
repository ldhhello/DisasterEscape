#pragma once

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include "ImageLayer.h"

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