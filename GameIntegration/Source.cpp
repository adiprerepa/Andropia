#include "Map.h"
#include <iostream>
#include <Windows.h>
#include "ColorStrings.h"


int main()
{
	while (true)
	{
		BioMap::map_t map = BioMap::Generator::generate();

		BioMap::printMap(map);

		std::cin.get();
	}
}