#include "Game.h"

Image game_image[10];

void Game_modal()
{
	Game game;
	memset(&game, 0, sizeof(Game));

	Image a = { "D:\\start.bmp", 0, 0 };
	game_image[0] = a;

	image_layer.imageCount = 1;
	image_layer.images = game_image;

	image_layer.renderAll(&image_layer);

	Sleep(3000);
}