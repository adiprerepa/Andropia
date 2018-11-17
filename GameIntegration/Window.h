#pragma once
#include "SDL_rect.h"

#define WINDOWNAME "GraphicsTest"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 800

namespace Window
{
	void init();
	void update();
	void destroy();
};

struct SDL_Texture;
struct SDL_Surface;

namespace Render
{
	SDL_Texture * createTextureFromSurface(SDL_Surface * surface);

	void blit(SDL_Texture * tex, SDL_Rect dest);

	void blitEx(SDL_Texture * tex, SDL_Rect dest, double angle, SDL_Point center);
};