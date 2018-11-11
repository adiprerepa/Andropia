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

int LandMap::neighborCountLand(LandMap::map_t& map, uint8_t x, uint8_t y, bool includeEdges, bool onlyAdjacents, int farness)
{
	int count = 0;
	for (int y2 = -farness; y2 <= farness; ++y2)
	{
		for (int x2 = -farness; x2 <= farness; ++x2)
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

int LandMap::neighborCountWater(LandMap::map_t& map, uint8_t x, uint8_t y, bool includeEdges, bool onlyAdjacents, int farness)
{
	int count = 0;
	for (int y2 = -farness; y2 <= farness; ++y2)
	{
		for (int x2 = -farness; x2 <= farness; ++x2)
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
	Color::printcolor("\t   ");
	for (uint8_t x = 0; x < mapw; ++x)
	{
		std::string str = (std::to_string(x) + " ").substr(0, 2);
		Color::printcolor(str);
	}
	Color::printcolor("\n");

	for (uint8_t y = 0; y < maph; ++y)
	{
		Color::printcolor("\t");		
		Color::printcolor((std::to_string(y) + "  ").substr(0, 3));

		for (uint8_t x = 0; x < mapw; ++x)
		{
			Biomes::biome_t& biome = map[y][x];

			switch (biome.stat)
			{
			case (Biomes::STAT_PLAIN_CLEAR):
			{
				if (biome.hasResource)
				{
					Color::printcolor(".o", Color::COLOR_RED);
					break;
				}
				Color::printcolor("XX", Color::COLOR_BGREEN);
				break;
			}
			case (Biomes::STAT_PLAIN_GRASS):
			{
				Color::printcolor("==", Color::COLOR_BGREEN);
				break;
			}
			case (Biomes::STAT_WATER_SHALLOW):
			{
				if (biome.hasResource)
				{
					Color::printcolor("0<", Color::COLOR_BBLUE);
					break;
				}
				Color::printcolor("~~", Color::COLOR_BBLUE);
				break;
			}
			case (Biomes::STAT_WATER_DEEP):
			{
				if (biome.hasResource)
				{
					Color::printcolor("0<", Color::COLOR_BLUE);
					break;
				}
				Color::printcolor("~~", Color::COLOR_BLUE);
				break;
			}
			case (Biomes::STAT_MOUNTAIN_CLEAR):
			{
				if (biome.hasResource)
				{
					Color::printcolor("^", Color::COLOR_BYELLOW);
					Color::printcolor("\\", Color::COLOR_BWHITE);
					break;
				}
				Color::printcolor("/^", Color::COLOR_BWHITE);
				break;
			}
			case (Biomes::STAT_FOREST_CLEAR):
			{
				if (biome.hasResource)
				{
					Color::printcolor(".", Color::COLOR_GRAY);
					Color::printcolor("|", Color::COLOR_GREEN);
					break;
				}
				Color::printcolor("||", Color::COLOR_GREEN);
				break;
			}
			case (Biomes::STAT_VILLAGE_UNCLAIMED):
			{
				Color::printcolor("<>", Color::COLOR_YELLOW);
				break;
			}
			}

		}
		Color::printcolor("\n");
	}

	Color::printcolor("\n");
}

int BioMap::findNeighbor(map_t& map, uint8_t x, uint8_t y, Biomes::state_t stat, int farness)
{
	for (int y2 = -farness; y2 <= farness; ++y2)
	{
		for (int x2 = -farness; x2 <= farness; ++x2)
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
			int farnbsl = LandMap::neighborCountLand(lmap, x, y, false, true, 2);
			int nbsw = LandMap::neighborCountWater(lmap, x, y, false, true);

			if (!lmap[y][x])
			{
				if (nbsl)
				{
					map[y][x].stat = Biomes::STAT_WATER_SHALLOW;
					if (Random::random() < spawnChanceFish)
					{
						map[y][x].hasResource = true;
					}
				}
				else
				{
					map[y][x].stat = Biomes::STAT_WATER_DEEP;
					if (farnbsl && Random::random() < spawnChanceWhale)
					{
						map[y][x].hasResource = true;
					}
				}
			}
			else
			{
				if (!nbsw && Random::random() < spawnChanceMountain)
				{
					map[y][x].stat = Biomes::STAT_MOUNTAIN_CLEAR;
					if (Random::random() < spawnChanceGold)
					{
						map[y][x].hasResource = true;
					}
				}
				else if (Random::random() < spawnChanceForest)
				{
					map[y][x].stat = Biomes::STAT_FOREST_CLEAR;
					if (Random::random() < spawnChanceHunt)
					{
						map[y][x].hasResource = true;
					}
				}
				else
				{
					if (Random::random() < spawnChanceGrass)
					{
						map[y][x].stat = Biomes::STAT_PLAIN_GRASS;
					}
					else
					{
						map[y][x].stat = Biomes::STAT_PLAIN_CLEAR;
						if (Random::random() < spawnChanceFruit)
						{
							map[y][x].hasResource = true;
						}
					}
				}
			}
		}
	}

}

void BioMap::Generator::placeVillages(map_t& map)
{
	biovec fields;

	for (uint8_t y = 0; y < maph; ++y)
	{
		for (uint8_t x = 0; x < mapw; ++x)
		{
			if (map[y][x].stat == Biomes::STAT_PLAIN_CLEAR)
			{
				fields.push_back({ &map[y][x], { x, y } });
			}
		}
	}

	while (fields.size())
	{
		auto village = Random::random_element(fields.begin(), fields.end());
		if (village != fields.end())
		{
			village->first->stat = Biomes::STAT_VILLAGE_UNCLAIMED;

			uint8_t vx = village->second.first;
			uint8_t vy = village->second.second;

			fields.erase(village);

			auto i = std::begin(fields);
			while (i != std::end(fields)) 
			{
				uint8_t fx = i->second.first;
				uint8_t fy = i->second.second;

				if (abs(fx - vx) + abs(fy - vy) < villageSpawnDistance)
				{
					i = fields.erase(i);
				}
				else
				{
					++i;
				}
			}

		}
		else
		{
			break;
		}
	}

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

