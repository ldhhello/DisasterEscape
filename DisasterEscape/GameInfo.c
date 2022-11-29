#include "GameInfo.h"

void GameInfo_modal()
{
	//image_layer.clearImage(&image_layer, false);

	Image im = { "", SCREEN_X * 16 / 2, SCREEN_Y * 16 / 2, 2.3, 0, bitmap_gameinfo, true };

	image_layer.imageCount = 1;
	image_layer.images = &im;

	image_layer.fadeIn(&image_layer, NULL);

	while (true)
	{
		int a = _getch();
		if (a == VK_RETURN || a == VK_SPACE)
			break;
	}

	image_layer.fadeOut(&image_layer, NULL);
}