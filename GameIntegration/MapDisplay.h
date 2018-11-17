#pragma once
#include "Map.h"
#include "SDL_rect.h"

struct Camera
{
	SDL_Point state;

	void set(SDL_Point position)
	{
		state = position;
	}

	void move(SDL_Point movement)
	{
		state.x += movement.x;
		state.y += movement.y;
	}

	SDL_Point apply(SDL_Point point)
	{
		return { point.x - state.x, point.y - state.y };
	}
};

class Display
{
	static void display(BioMap::map_t& map);
};