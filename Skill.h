#pragma once
#include "stdafx.h"
#include "CharacterClass.h"

class Skill
{
	std::string name;
	std::string ability;

	bool is_general; // is this a skill that anyone can use?
	bool is_class_skill; // is this a class skill of the character?

	int ranks; // how many ranks does this skill have?

	friend class Character; // allow class Character to access these private members
	friend void saveSkillStructure(std::ostream& file, Skill skill_structure[35]);
	friend void loadSkillStructure(std::istream& file, Skill * skill_structure, std::string* err);
public:
	void setClassSkill(bool is_class_skill);

	Skill getSkill(std::string name);
	// note: usage would be, for example, `character.getSkillName(skill_structure->getSkill(__name__))` instead of `character.getSkillName(i)`

	Skill(std::string name, std::string ability, bool is_general);
	Skill();
	~Skill();
};

// NOTE:
// Rename all variables relating to skills in CharacterClass and ClassData...make them easier to understand
