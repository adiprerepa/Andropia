#include "Game.h"
#include <iostream>
#include "Skills.h"
#include "ColorStrings.h"
#include <conio.h>
#include "Window.h"
#include "Texture.h"
#include "MapDisplay.h"

std::vector<Game::Object*> Game::objects;

BioMap::map_t Game::map;

void Game::main()
{
	Window::init();
	TextureManager::loadparts("bob,jeff,stevie,bills", "bob.png", { 64, 64 }, { 2,2 });

	Camera c;

	c.set({ 10, 10 });

	uint8_t in;

	while (true)
	{
		in = _getch();

		TextureManager::render("bob", { 100, 100 });

		Window::update();

		switch (in)
		{
		case 'e':
		{
			Window::destroy();
			TextureManager::destroy();
			return;
		}
		case 'w':
		{
			break;
		}
		case 's':
		{
			break;
		}
		case 'a':
		{
			break;
		}
		case 'd':
		{
			break;
		}
		}
	}


	//unsigned int selectx = 0, selecty = 0;

	//BioMap::map_t map = BioMap::Generator::generate();

	//while (true)
	//{
	//	system("cls");
	//	BioMap::printMap(map, selectx, selecty);

	//	char c = _getch();
	//	_getch();
	//	if (c)
	//	{
	//		switch (c)
	//		{
	//		case ('w'):
	//		{
	//			if (selecty > 0) selecty--;
	//			break;
	//		}
	//		case ('a'):
	//		{
	//			if (selectx > 0) selectx--;
	//			break;
	//		}
	//		case ('s'):
	//		{
	//			if (selecty < mapw - 1) selecty++;
	//			break;
	//		}
	//		case ('d'):
	//		{
	//			if (selectx < maph - 1) selectx++;
	//			break;
	//		}
	//		}
	//	}
	//}

	//std::cin.get();
}
