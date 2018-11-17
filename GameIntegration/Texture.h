#pragma once
#include <string>
#include "SDL_rect.h"
#include "SDL_pixels.h"

struct SDL_Texture;

class TextureManager;

class Texture
{
private:
	SDL_Point size;

	SDL_Texture * tex = nullptr;

public:

	Texture();
	Texture(SDL_Texture * tex);
	~Texture();

	void load(std::string filename);
	void loadpart(std::string filename, SDL_Rect part);

	void render(SDL_Point pos);
	void render(SDL_Point pos, double theta);
	void render(SDL_Point pos, SDL_Point spincenter, double theta);

	friend TextureManager;
};

class TextureManager
{
public:
	static void destroy();

	static Texture * find(std::string name);

	static void render(std::string name, SDL_Point pos);
	static void render(std::string name, SDL_Point pos, double theta);
	static void render(std::string name, SDL_Point pos, SDL_Point spincenter, double theta);

	static void makeWord(std::string name, std::string text, std::string fontPath, int fontSize, SDL_Color forecolor, SDL_Color backcolor);

	static void load(std::string name, std::string filename);
	static void loadpart(std::string name, std::string filename, SDL_Rect part);
	static void loadparts(std::string name, std::string filename, SDL_Point partsize, SDL_Point imagesize);
};