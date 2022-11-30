#pragma once
#pragma comment (lib, "Msimg32.lib")
#include <Windows.h>
#include "ImageLayer.h"

// 마개조 by Donghyun Lee (https://github.com/ldhhello)

#ifndef IMAGE_LAYER_IMPL_H
#define IMAGE_LAYER_IMPL_H

#define CONSOLE_WIDTH 180
#define CONSOLE_HEIGHT 48

#define DEFAULT_RESOLUTION_SCALE 16

extern double RESOLUTION_MULTIPLIER;

// in main.c
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

typedef struct {
	int width, height;
}Size;

inline int getDPI(HWND hWnd) {
	const HANDLE user32 = GetModuleHandle(TEXT("user32"));
	const FARPROC func = GetProcAddress((HMODULE)user32, "GetDpiForWindow");
	if (func == NULL)
		return 96;
	return ((UINT(__stdcall*)(HWND))func)(hWnd);
}

inline Size getBitmapSize(HBITMAP bitmap) {
	BITMAP tmpBitmap;
	GetObject(bitmap, sizeof(BITMAP), &tmpBitmap);
	const Size bitmapSize = { tmpBitmap.bmWidth, tmpBitmap.bmHeight };
	return bitmapSize;
}

inline HDC createNewBackDC(HDC compatibleDC) {
	const HDC backDC = CreateCompatibleDC(compatibleDC);
	const HBITMAP backBitmap = CreateCompatibleBitmap(compatibleDC, WINDOW_WIDTH, WINDOW_HEIGHT);
	SelectObject(backDC, backBitmap);
	DeleteObject(backBitmap);
	return backDC;
}

inline void putBitmapToBackDC(HDC backDC, Image image, UINT transparentColor) {
	const HDC bitmapDC = CreateCompatibleDC(backDC);
	HBITMAP bitmap;

	int no_delete = 0;

	if (image.fileName[0] != 0)
		bitmap = (HBITMAP)LoadImage(NULL, (LPCSTR)image.fileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	else
	{
		bitmap = image.bitmap;
		no_delete = 1;
	}

	SelectObject(bitmapDC, bitmap);

	double scale = image.scale * RESOLUTION_MULTIPLIER;
	if (scale == 0) scale = DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER;

	int x = (int)(image.x * RESOLUTION_MULTIPLIER);
	int y = (int)(image.y * RESOLUTION_MULTIPLIER);
	const Size bitmapSize = getBitmapSize(bitmap);
	const int width = (int)(bitmapSize.width * scale);
	const int height = (int)(bitmapSize.height * scale);

	if (image.isCenter)
	{
		x -= width / 2;
		y -= height / 2;
	}

	TransparentBlt(backDC, x, y, width, height,
		bitmapDC, 0, 0, bitmapSize.width, bitmapSize.height, transparentColor);

	if(!no_delete)
		DeleteObject(bitmap);

	DeleteDC(bitmapDC);
}

inline void applyToDC(HDC dstDC, HDC srcDC) {
	BitBlt(dstDC, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
		srcDC, 0, 0, SRCCOPY);
}

inline void _initialize(ImageLayer* self) {
	self->_windowHandle = GetConsoleWindow();
	self->_consoleDC = GetDC(self->_windowHandle);

	const int dpi = getDPI(self->_windowHandle);
	RESOLUTION_MULTIPLIER = dpi / 192.0;
	WINDOW_WIDTH = (int)(CONSOLE_WIDTH * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
	WINDOW_HEIGHT = (int)(CONSOLE_HEIGHT * 2 * DEFAULT_RESOLUTION_SCALE * RESOLUTION_MULTIPLIER);
}

inline HDC getRenderedBackDC(ImageLayer* self) {
	const HDC backDC = createNewBackDC(self->_consoleDC);

	for (int i = 0; i < self->imageCount; i++) {
		if (!self->images[i].isHide)
			putBitmapToBackDC(backDC, self->images[i], self->transparentColor);
	}
	return backDC;
}

inline void _renderAll(ImageLayer* self) {
	const HDC backDC = getRenderedBackDC(self);
	if (self->applyToDC != NULL) self->applyToDC(backDC);
	applyToDC(self->_consoleDC, backDC);
	DeleteDC(backDC);
}

// _startRender, _endRender: 렌더링을 시작/중지한다
// _startRender가 호출되면 현재 imagelayer 상황을 bufferDC에 저장하고, _endRender가 호출되면 bufferDC를 화면에 쓴 뒤 bufferDC를 지운다
// 이미지 위에 텍스트 등을 그릴 때 유용하게 쓸 수 있다 (더블 버퍼링이 제대로 돼서 화면이 깜박거리지 않음)
inline void _startRender(ImageLayer* self) {
	if (self->bufferDC != NULL)
		return;

	self->bufferDC = getRenderedBackDC(self);
}

inline void _endRender(ImageLayer* self) {
	if (self->bufferDC == NULL)
		return;

	if (self->applyToDC != NULL) self->applyToDC(self->bufferDC);
	applyToDC(self->_consoleDC, self->bufferDC);
	DeleteDC(self->bufferDC);

	self->bufferDC = NULL;
}

// _appendImage, _eraseImage, _clearImage : ImageLayer를 스택처럼 쓸수 있게 해주는 함수
// _appendImage는 이미지레이어의 images 배열 맨 뒤에 이미지를 하나 추가한다
// _eraseImage는 하나 없애고, _clearImage는 모두 없앤다!
// 이걸 제대로 사용하기 위해서는 images 배열에 여유 공간이 충분히 있어야 한다 (특히 appendImage는 images 배열 크기보다 imageCount가 작아야 한다)
inline void _appendImage(ImageLayer* self, Image im, int redraw)
{
	self->images[self->imageCount] = im;
	self->imageCount++;

	if (redraw)
		self->renderAll(self);
}

inline void _eraseImage(ImageLayer* self, int redraw)
{
	self->imageCount--;

	if(redraw)
		self->renderAll(self);
}

inline void _clearImage(ImageLayer* self, int redraw)
{
	self->imageCount = 0;

	if (redraw)
		self->renderAll(self);
}

#endif