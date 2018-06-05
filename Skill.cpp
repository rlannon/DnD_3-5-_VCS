#include "Skill.h"

void Skill::setClassSkill(bool is_class_skill) {
	Skill::is_class_skill = is_class_skill;
}

std::string Skill::getSkillName() {
	return Skill::name;
}

std::string Skill::getSkillAbility() {
	return Skill::ability;
}

Skill Skill::getSkill(std::string name) {
	for (int i = 0; i < num_skills; i++) {
		if (name == this[i].name) {
			return this[i];
		}
	}
}

bool Skill::isUntrained() {
	return this->untrained;
}

int Skill::getMaxRanks(int level) {
	if (Skill::is_class_skill) {
		return(4 + level);
	}
	else if (!Skill::is_class_skill && Skill::untrained) {
		return ((4 + level) / 2);
	}
	else if (!Skill::untrained) {
		return 0;
	}
}

Skill::Skill(std::string name, std::string ability, bool is_general)
{
	Skill::name = name;
	Skill::ability = ability;
	Skill::untrained = is_general;
	Skill::is_class_skill = 0;
	Skill::ranks = 0;
}

Skill::Skill() {
	Skill::name = "";
	Skill::ability = "";
	Skill::untrained = 0;
	Skill::is_class_skill = 0;
	Skill::ranks = 0;
}

Skill::~Skill()
{
}
