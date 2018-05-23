#include "Skill.h"

void Skill::setClassSkill(bool is_class_skill) {
	Skill::is_class_skill = is_class_skill;
}

Skill Skill::getSkill(std::string name) {
	for (int i = 0; i < 35; i++) {
		if (name == this[i].name) {
			return this[i];
		}
	}
}

Skill::Skill(std::string name, std::string ability, bool is_general)
{
	Skill::name = name;
	Skill::ability = ability;
	Skill::is_general = is_general;
	Skill::is_class_skill = 0;
	Skill::ranks = 0;
}

Skill::Skill() {
	Skill::name = "";
	Skill::ability = "";
	Skill::is_general = 0;
	Skill::is_class_skill = 0;
	Skill::ranks = 0;
}

Skill::~Skill()
{
}
