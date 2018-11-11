#include "Game.h"
#include <iostream>
#include "Skills.h"

std::vector<Game::Object*> Game::objects;

BioMap::map_t Game::map;

void Game::main()
{
	/// DEMO GEN
	//while (true)
	//{
	//	BioMap::map_t map = BioMap::Generator::generate();
	//	BioMap::printMap(map);
	//	std::cin.get();
	//}

	/// DEMO SKILLTREE
	//SkillTree st;
	//st.add("n");
	//st.add("n1", "n");
	//st.add("n2", "n");
	//st.add("n3", "n");
	//st.add("n11", "n1");
	//st.add("n12", "n1");
	//st.add("n13", "n1");
	//st.add("n21", "n2");
	//st.add("n22", "n2");
	//st.add("n23", "n2");
	//st.add("n31", "n3");
	//st.add("n32", "n3");
	//st.add("n33", "n3");
	//std::string buf;
	//while (true)
	//{
	//	std::getline(std::cin, buf);
	//	st.get(buf);
	//}

}
