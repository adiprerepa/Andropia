#pragma once
#include <array>
#include <bitset>
#include <vector>

typedef std::vector<std::pair<uint8_t, uint8_t>> pointset;

const uint8_t mapw = 50;
const uint8_t maph = 50;

namespace LandMap
{
	typedef std::array<std::bitset<mapw>, maph> map_t;

	void printMap(map_t& map);

	int neighborCountLand(map_t& map, uint8_t x, uint8_t y, bool includeEdges = true, bool onlyAdjacents = false);
	int neighborCountWater(map_t& map, uint8_t x, uint8_t y, bool includeEdges = true, bool onlyAdjacents = false);


	namespace Generator
	{
		const int deathLimit = 2;
		const int birthLimit = 2;
		const int stepCount = 2;
		const float chanceToStartAlive = 0.1f;
		const float chanceOfEndIsWall = 0.3f;

		void minit(map_t& map);

		void simStep(map_t& map);

		void finalStep(map_t& map);

		map_t generate();
	}
}

namespace BioMap
{
	namespace Dudes
	{
		struct dude
		{
			uint8_t x;
			uint8_t y;
			uint8_t health : 6;
			uint8_t type : 4;
			uint8_t usable : 1;
			uint8_t state : 5;
		};
	}

	namespace Biomes
	{
		typedef enum
		{
			SPEC_JAP = 0, // japan, blossom
			SPEC_IMP = 1, // grasslands
			SPEC_BRD = 2, // snowy
			SPEC_UMJ = 3, // desert
		} specialty_t;

		typedef enum
		{
			// plain						//forest						// water						// mountain						// city
			STAT_PLAIN_CLEAR,				STAT_FOREST_CLEAR,				STAT_WATER_SHALLOW,				STAT_MOUNTAIN_CLEAR,			STAT_VILLAGE_UNCLAIMED,
			STAT_PLAIN_GRASSY,												STAT_WATER_FISH,				STAT_MOUNTAIN_GOLD,
			STAT_PLAIN_FARM,												STAT_WATER_DEEP,				STAT_MOUNTAIN_MINE,
																			STAT_WHALE_WATER,
		} state_t;

		typedef enum
		{
			
		} accessory_t;

		struct biome_t
		{
			specialty_t spec : 5; // dependent on type, see enum
			state_t stat : 17; // dependent on type, see enum
			Dudes::dude * dude;
		};
	}

	typedef std::array<std::array<Biomes::biome_t, mapw>, maph> map_t;

	void printMap(map_t& map);

	int findNeighbor(map_t& map, uint8_t x, uint8_t y, Biomes::state_t stat);

	namespace Generator
	{
		const float mountainSpawnChance = .2;
		const float forestSpawnChance = 0;

		void geoCopy(LandMap::map_t& lmap, map_t& map);

		void placeVillages(map_t& map);
		
		map_t generate(LandMap::map_t lmap);
		map_t generate();
	}
}
