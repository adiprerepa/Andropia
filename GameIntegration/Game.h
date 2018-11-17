#pragma once
#include "Map.h"

namespace Game
{
	extern std::vector<Object*> objects;

	extern BioMap::map_t map;

	void main();

	typedef enum
	{
		OBJT_DUDE,
		OBJT_CITY,
		OBJT_STRUCTURE,
	} ObjectType;

	struct Object
	{
		uint8_t x;
		uint8_t y;

		virtual bool autoUpdate();

		virtual bool move();

		virtual bool destroy();

		virtual bool update();
	};
};