#pragma once
#include <Windows.h>

// 마개조 by Donghyun Lee (https://github.com/ldhhello)

#ifndef IMAGE_LAYER_INTERFACE_H
#define IMAGE_LAYER_INTERFACE_H

typedef struct {
	char* fileName;
	int x, y;
	double scale;
	int isHide;

	HBITMAP bitmap;
}Image;

typedef struct _ImageLayer {
	Image* images;
	int imageCount;
	UINT transparentColor;

	HWND _windowHandle;
	HDC _consoleDC;

	HDC bufferDC;

	void (*initialize)(struct _ImageLayer*);
	void (*renderAll)(struct _ImageLayer*);
	void (*fadeIn)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
	void (*fadeOut)(struct _ImageLayer*, void(*applyToBackDC)(HDC));
	void (*applyToDC)(HDC);

	// ImageLayer 외의 다른 작업 시 화면 깜박임 현상 방지를 위한 더블 버퍼링 관련 코드!!
	void (*startRender)(struct _ImageLayer*);
	void (*endRender)(struct _ImageLayer*);
}ImageLayer;

#endif