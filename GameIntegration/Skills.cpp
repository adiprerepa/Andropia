#include "Skills.h"
#include <iostream>

Skill::Skill(const std::string name, Skill * req) : name(name), req(req), got(false)
{
}

const char Skill::get()

{
	if (got)
	{
		return 1;
	}
	else if (req)
	{
		if (req->got)
		{
			got = true;
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		got = true;
		return 0;
	}
}

bool SkillTree::add(const std::string name, std::string reqname)
{
	if (find(name))
	{
		return 0;
	}
	if (reqname != "")
	{
		skills.push_back(new Skill(name, find(reqname)));
	}
	else 
	{
		skills.push_back(new Skill(name, find(reqname)));
	}
	return 1;
}

Skill * SkillTree::find(std::string name) const
{
	for (auto& skill : skills)
	{
		if (skill->name == name)
		{
			return skill;
		}
	}
	return NULL;
}

char SkillTree::get(std::string name)
{
	if (auto s = find(name))
	{
		return s->get();
	}
	return 3;
}

inline const bool SkillTree::isGot(std::string name) const
{
	if (auto s = find(name))
	{
		return s->isGot();
	}
	return 0;
}

void SkillTree::destroy()
{
	for (auto skill : skills)
	{
		delete skill;
	}
	skills.clear();
}

SkillTree::~SkillTree()
{
	destroy();
}

