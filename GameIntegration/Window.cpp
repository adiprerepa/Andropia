#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "Window.h"

SDL_Window * WINDOW_WINDOW = nullptr;
SDL_Renderer * WINDOW_RENDERER = nullptr;

SDL_Texture * Render::createTextureFromSurface(SDL_Surface * surface)
{
	SDL_Texture * t = SDL_CreateTextureFromSurface(WINDOW_RENDERER, surface);
	SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
	return t;
}

void Render::blit(SDL_Texture * tex, SDL_Rect dest)
{
	SDL_RenderCopy(WINDOW_RENDERER, tex, nullptr, &dest);
}

void Render::blitEx(SDL_Texture * tex, SDL_Rect dest, double angle, SDL_Point spincenter)
{
	SDL_RenderCopyEx(WINDOW_RENDERER, tex, nullptr, &dest, angle, &spincenter, SDL_FLIP_NONE);
}


void Window::init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG);
	TTF_Init();

	WINDOW_WINDOW = SDL_CreateWindow(WINDOWNAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, NULL);
	WINDOW_RENDERER = SDL_CreateRenderer(WINDOW_WINDOW, -1, SDL_RENDERER_ACCELERATED);

	//SDL_SetRenderDrawBlendMode(WINDOW_RENDERER, SDL_BLENDMODE_BLEND);
}

void Window::destroy()
{
	SDL_DestroyWindow(WINDOW_WINDOW);
	SDL_DestroyRenderer(WINDOW_RENDERER);
}

void Window::update()
{
	SDL_RenderPresent(WINDOW_RENDERER);
	SDL_SetRenderDrawColor(WINDOW_RENDERER, 255, 255, 255, 255);;
	SDL_RenderClear(WINDOW_RENDERER);
	
}
