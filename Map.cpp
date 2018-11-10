#include "Map.h"
#include "Random.h"
#include "ColorStrings.h"

void LandMap::printMap(LandMap::map_t& map)
{
	for (uint8_t y = 0; y < maph; ++y)
	{
		for (uint8_t x = 0; x < mapw; ++x)
		{
			if (map[y][x])
			{
				Color::printcolor("XX", Color::Color::COLOR_GREEN);
			}
			else
			{
				Color::printcolor("~~", Color::Color::COLOR_BLUE);
			}
		}
		Color::printcolor("\n");
	}
}

int LandMap::neighborCountLand(LandMap::map_t& map, uint8_t x, uint8_t y, bool includeEdges, bool onlyAdjacents)
{
	int count = 0;
	for (int y2 = -1; y2 <= 1; ++y2)
	{
		for (int x2 = -1; x2 <= 1; ++x2)
		{
			int neighbor_x = x + x2;
			int neighbor_y = y + y2;

			if (!(x2 || y2))
			{
			}
			else if (onlyAdjacents && (x2 * y2)) // if both are nonzero (so its non-adjacent), product = true. This condition must be met when they are non-adjacent, to prevent the last elif from running
			{
			}
			else if (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= mapw || neighbor_y >= maph)
			{
				if (includeEdges && Random::random() < Generator::chanceOfEndIsWall)
				{
					++count;
				}
			}
			else if (map[neighbor_y][neighbor_x])
			{
				++count;
			}
		}
	}

	return count;
}

int LandMap::neighborCountWater(LandMap::map_t& map, uint8_t x, uint8_t y, bool includeEdges, bool onlyAdjacents)
{
	int count = 0;
	for (int y2 = -1; y2 <= 1; ++y2)
	{
		for (int x2 = -1; x2 <= 1; ++x2)
		{
			int neighbor_x = x + x2;
			int neighbor_y = y + y2;

			if (!(x2 || y2))
			{
			}
			else if (onlyAdjacents && (x2 * y2)) // if both are nonzero (so its non-adjacent), product = true. This condition must be met when they are non-adjacent, to prevent the last elif from running
			{
			}
			else if (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= mapw || neighbor_y >= maph)
			{
				if (includeEdges && Random::random() < Generator::chanceOfEndIsWall)
				{
					++count;
				}
			}
			else if (!map[neighbor_y][neighbor_x])
			{
				++count;
			}
		}
	}

	return count;
}

void LandMap::Generator::minit(LandMap::map_t& map)
{
	for (uint8_t y = 0; y < maph; ++y)
	{
		for (uint8_t x = 0; x < mapw; ++x)
		{
			if (Random::random() < chanceToStartAlive)
			{
				map[y][x] = true;
			}
		}
	}
}

void LandMap::Generator::simStep(LandMap::map_t& map)
{
	map_t newMap;

	for (uint8_t x = 0; x < mapw; ++x)
	{
		for (uint8_t y = 0; y < maph; ++y)
		{
			int nbs = neighborCountLand(map, x, y, true);

			if (map[y][x])
			{
				if (nbs < deathLimit)
				{
					newMap[y][x] = false;
				}
				else
				{
					newMap[y][x] = true;
				}
			}
			else
			{
				if (nbs < birthLimit)
				{
					newMap[y][x] = false;
				}
				else
				{
					newMap[y][x] = true;
				}
			}
		}
	}

	map = newMap;
}

void LandMap::Generator::finalStep(map_t & map)
{
	map_t newMap = map;

	do
	{
		map = newMap;
		for (uint8_t x = 0; x < mapw; ++x)
		{
			for (uint8_t y = 0; y < maph; ++y)
			{
				int nbsl = neighborCountLand(map, x, y, false);
				int nbsw = neighborCountWater(map, x, y, false);

				if (map[y][x] && nbsl <= 1) // if nbs == 0, it is a lone island, if nbs == 1, it is a bad edge, delete
				{
					newMap[y][x] = false;
				}


				if (!map[y][x] && nbsw <= 1) // if nbs == 0, it is a lone island, if nbs == 1, it is a bad edge, delete
				{
					newMap[y][x] = true;
				}
			}
		}
	} while (newMap != map); // if newMap != map, repeat edge-cull process
}


LandMap::map_t LandMap::Generator::generate()
{
	map_t map;

	minit(map);

	for (int i = 0; i < stepCount; i++) simStep(map);

	finalStep(map);

	return map;
}

void BioMap::printMap(map_t& map)
{
	for (uint8_t y = 0; y < maph; ++y)
	{
		Color::printcolor("\t");
		for (uint8_t x = 0; x < mapw; ++x)
		{
			Biomes::biome_t& biome = map[y][x];

			if (biome.stat == Biomes::STAT_PLAIN_CLEAR)
			{
				Color::printcolor("XX", Color::COLOR_GREEN);
			}
			if (biome.stat == Biomes::STAT_WATER_SHALLOW)
			{
				Color::printcolor("~~", Color::COLOR_BBLUE);
			}
			if (biome.stat == Biomes::STAT_WATER_DEEP)
			{
				Color::printcolor("~~", Color::COLOR_BLUE);
			}
			if (biome.stat == Biomes::STAT_MOUNTAIN_CLEAR)
			{
				Color::printcolor("^^", Color::COLOR_BWHITE);
			}
			if (biome.stat == Biomes::STAT_VILLAGE_UNCLAIMED)
			{
				Color::printcolor("<>", Color::COLOR_YELLOW);
			}

		}
		Color::printcolor("\n");
	}

	Color::printcolor("\n");
}

int BioMap::findNeighbor(map_t& map, uint8_t x, uint8_t y, Biomes::state_t stat)
{
	for (int y2 = -1; y2 <= 1; ++y2)
	{
		for (int x2 = -1; x2 <= 1; ++x2)
		{
			int neighbor_x = x + x2;
			int neighbor_y = y + y2;

			if (!(x2 || y2))
			{
			}
			else if (neighbor_x < 0 || neighbor_y < 0 || neighbor_x >= mapw || neighbor_y >= maph)
			{
			}
			else if (map[neighbor_y][neighbor_x].stat = stat)
			{
				return true;
			}
		}
	}

	return false;
}

void BioMap::Generator::geoCopy(LandMap::map_t& lmap, map_t& map)
{
	for (uint8_t y = 0; y < maph; ++y)
	{
		for (uint8_t x = 0; x < mapw; ++x)
		{
			int nbsl = LandMap::neighborCountLand(lmap, x, y, false, true);
			int nbsw = LandMap::neighborCountWater(lmap, x, y, false, true);

			if (!lmap[y][x])
			{
				if (nbsl)
				{
					map[y][x].stat = Biomes::STAT_WATER_SHALLOW;
				}
				else
				{
					map[y][x].stat = Biomes::STAT_WATER_DEEP;
				}
			}
			else
			{
				if (!nbsw && Random::random() < mountainSpawnChance)
				{
					map[y][x].stat = Biomes::STAT_MOUNTAIN_CLEAR;
				}
				else if (Random::random() < forestSpawnChance)
				{
					map[y][x].stat = Biomes::STAT_FOREST_CLEAR;
				}
				else
				{
					map[y][x].stat = Biomes::STAT_PLAIN_CLEAR;
				}
			}
		}
	}

}

void BioMap::Generator::placeVillages(map_t & map)
{
}

BioMap::map_t BioMap::Generator::generate(LandMap::map_t lmap)
{
	map_t map;

	geoCopy(lmap, map);

	placeVillages(map);

	return map;
}

BioMap::map_t BioMap::Generator::generate()
{
	return BioMap::Generator::generate(LandMap::Generator::generate());
}

