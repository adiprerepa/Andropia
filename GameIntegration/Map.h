#pragma once
#include <array>
#include <bitset>
#include <vector>

const uint8_t mapw = 50;
const uint8_t maph = 50;

namespace LandMap
{
	typedef std::array<std::bitset<mapw>, maph> map_t;

	void printMap(map_t& map);

	int neighborCountLand(map_t& map, uint8_t x, uint8_t y, bool includeEdges = true, bool onlyAdjacents = false, int farness = 1);
	int neighborCountWater(map_t& map, uint8_t x, uint8_t y, bool includeEdges = true, bool onlyAdjacents = false, int farness = 1);


	namespace Generator
	{
		const int deathLimit = 2;
		const int birthLimit = 2;
		const int stepCount = 2;
		const double chanceToStartAlive = .1f;
		const double chanceOfEndIsWall = .3f;

		void minit(map_t& map);

		void simStep(map_t& map);

		void finalStep(map_t& map);

		map_t generate();
	}
}

namespace Game
{
	class Object;
}

namespace BioMap
{

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
			STAT_PLAIN_FRUIT,				STAT_FOREST_HUNT,				STAT_WATER_FISH,				STAT_MOUNTAIN_GOLD,
			STAT_PLAIN_FARM,												STAT_WATER_DEEP,				STAT_MOUNTAIN_MINE,
			STAT_PLAIN_GRASS,												STAT_WATER_WHALE,
		} state_t;

		typedef enum
		{
			
		} accessory_t;

		struct biome_t
		{
			specialty_t spec : 5; // dependent on type, see enum
			state_t stat : 17; // dependent on type, see enum
			Game::Object * gameobj;
		};
	}

	typedef std::array<std::array<Biomes::biome_t, mapw>, maph> map_t;

	typedef std::vector <std::pair<Biomes::biome_t *, std::pair<uint8_t, uint8_t>>> biovec;

	void printMap(map_t& map);

	int findNeighbor(map_t& map, uint8_t x, uint8_t y, Biomes::state_t stat, int farness = 1);

	namespace Generator
	{
		const double spawnChanceFish = 0.2;
		const double spawnChanceWhale = 0.05;
		const double spawnChanceMountain = .2;
		const double spawnChanceGold = .5;
		const double spawnChanceForest = .3;
		const double spawnChanceHunt = .4;
		const double spawnChanceFruit = 0.1;
		const double spawnChanceGrass = 0.1;
		const int villageSpawnDistance = 4;

		void geoCopy(LandMap::map_t& lmap, map_t& map);

		void placeVillages(map_t& map);
		
		map_t generate(LandMap::map_t lmap);
		map_t generate();
	}
}
