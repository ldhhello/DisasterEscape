#pragma once
#include <Windows.h>

// ������ by Donghyun Lee (https://github.com/ldhhello)

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

	// ImageLayer ���� �ٸ� �۾� �� ȭ�� ������ ���� ������ ���� ���� ���۸� ���� �ڵ�!!
	void (*startRender)(struct _ImageLayer*);
	void (*endRender)(struct _ImageLayer*);
}ImageLayer;

#endif