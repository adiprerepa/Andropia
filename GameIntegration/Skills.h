#pragma once
#include <vector>

class Skill
{
private:
	Skill * req;
	bool got = false;

public:
	const std::string name;

	Skill(const std::string name, Skill * req);

	const char get();

	inline const bool isGot() const { return got; }
};


class SkillTree
{
private:

public:
	std::vector<Skill*> skills;

	bool add(const std::string name, std::string reqname = "");

	Skill * find(std::string name) const;

	char get(std::string name);

	inline const bool isGot(std::string name) const;

	void destroy();

	~SkillTree();
};