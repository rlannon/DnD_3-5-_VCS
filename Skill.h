#pragma once
#include "stdafx.h"
#include "CharacterClass.h"

class Skill
{
	std::string name;
	std::string ability;

	bool is_class_skill; // is this a class skill of the character?
	bool is_general; // is this a skill that anyone can use?

	int ranks; // how many ranks does this skill have?

	friend class Character; // allow class Character to access these private members
public:
	void setClassSkill(bool is_class_skill);

	Skill(std::string name, std::string ability, bool is_general);
	~Skill();
};

// NOTE:
// Rename all variables relating to skills in CharacterClass and ClassData...make them easier to understand
