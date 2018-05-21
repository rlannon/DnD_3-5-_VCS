#include "Skill.h"

void Skill::setClassSkill(bool is_class_skill) {
	Skill::is_class_skill = is_class_skill;
}

Skill::Skill(std::string name, std::string ability, bool is_general)
{
	Skill::name = name;
	Skill::ability = ability;
	Skill::is_general = is_general;

	Skill::ranks = 0;
}


Skill::~Skill()
{
}
