#include "Texture.h"
#include "Window.h"

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include <vector>
#include <regex>

Texture::Texture()
{
	tex = nullptr;
}

Texture::Texture(SDL_Texture * tex)
{
	this->tex = tex;
	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

Texture::~Texture()
{
	if (tex) SDL_DestroyTexture(tex);
	tex = nullptr;
}

void Texture::load(std::string filename)
{
	SDL_Surface * temp = IMG_Load(filename.c_str());

	tex = Render::createTextureFromSurface(temp);

	SDL_FreeSurface(temp);

	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

void Texture::loadpart(std::string filename, SDL_Rect part)
{
	SDL_Surface * uncropped = IMG_Load(filename.c_str());
	SDL_Surface * temp =  SDL_CreateRGBSurface(uncropped->flags, part.w, part.h, uncropped->format->BitsPerPixel, uncropped->format->Rmask, uncropped->format->Gmask, uncropped->format->Bmask, uncropped->format->Amask);
	SDL_BlitSurface(uncropped, &part, temp, nullptr);

	tex = Render::createTextureFromSurface(temp);

	SDL_FreeSurface(temp);

	SDL_QueryTexture(tex, nullptr, nullptr, &size.x, &size.y);
}

void Texture::render(SDL_Point pos)
{
	Render::blit(tex, { pos.x, pos.y, size.x, size.y });
}

void Texture::render(SDL_Point pos, double theta)
{
	Render::blitEx(tex, { pos.x, pos.y, size.x, size.y }, theta, { pos.x + size.x / 2, pos.y + size.y / 2 });
}


void Texture::render(SDL_Point pos, SDL_Point spincenter, double theta)
{
	Render::blitEx(tex, { pos.x, pos.y, size.x, size.y }, theta, spincenter);
}

std::vector<std::pair<std::string, Texture*>> textures;

void TextureManager::load(std::string name, std::string filename)
{
	Texture * tex = new Texture();
	tex->load(filename);
	textures.push_back({ name, tex });
}

void TextureManager::loadpart(std::string name, std::string filename, SDL_Rect part)
{
	Texture * tex = new Texture();
	tex->loadpart(filename, part);
	textures.push_back({ name, tex });
}

void TextureManager::loadparts(std::string names, std::string filename, SDL_Point partsize, SDL_Point imagesize)
{
	std::string currentname;

	int pos1 = 0;
	for (int x = 0; x < imagesize.x; ++x)
	{
		for (int y = 0; y < imagesize.y; ++y)
		{

			int pos2 = names.find_first_of(",", pos1);

			if (pos2 != std::string::npos)
			{
				currentname = names.substr(pos1, pos2 - pos1);
			}
			else
			{
				currentname = names.substr(pos1);
			}

			SDL_Rect clip = { partsize.x * x, partsize.y * y, partsize.x, partsize.y };

			Texture * tex = new Texture();
			tex->loadpart(filename, clip);
			textures.push_back({ currentname, tex });

			if (pos2 == std::string::npos)
			{
				return;
			}

			pos1 = pos2 + 1;
		}
	}
}

void TextureManager::destroy()
{
	for (auto& tex : textures)
	{
		tex.second->~Texture();
		delete tex.second;
	}
	textures.clear();
}

Texture * TextureManager::find(std::string name)
{
	for (auto& tex : textures)
	{
		if (tex.first == name)
		{
			return tex.second;
		}
	}
	return nullptr;
}

void TextureManager::render(std::string name, SDL_Point pos)
{
	find(name)->render(pos);
}

void TextureManager::render(std::string name, SDL_Point pos, double theta)
{
	find(name)->render(pos, theta);
}

void TextureManager::render(std::string name, SDL_Point pos, SDL_Point spincenter, double theta)
{
	find(name)->render(pos, spincenter, theta);
}

void TextureManager::makeWord(std::string name, std::string text, std::string fontPath, int fontSize, SDL_Color forecolor, SDL_Color backcolor)
{
	TTF_Font* font = TTF_OpenFont(fontPath.c_str(), fontSize);

	SDL_Surface* surfaceMessage = TTF_RenderText_Shaded(font, text.c_str(), forecolor, backcolor);

	Texture * tex = new Texture(Render::createTextureFromSurface(surfaceMessage));

	textures.push_back({ name, tex });
}