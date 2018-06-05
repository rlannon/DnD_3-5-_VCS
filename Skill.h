#pragma once
#include "stdafx.h"

const int num_skills = 45;

class Skill
{
	std::string name;
	std::string ability;

	bool untrained; // is this a skill that anyone can use?
	bool is_class_skill; // is this a class skill of the character?

	int ranks; // how many ranks does this skill have?

	friend class Character; // allow class Character to access these private members
	friend class CharacterClass;
	friend class ClassData;

	friend void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);
	friend void loadClassData_RVC(std::istream& file, ClassData* class_obj);

	friend void saveSkillStructure(std::ostream& file, Skill skill_structure[num_skills]);
	friend void loadSkillStructure(std::istream& file, Skill * skill_structure);
	friend void createSkill();
public:
	void setClassSkill(bool is_class_skill);

	std::string getSkillName();
	std::string getSkillAbility();

	Skill getSkill(std::string name);
	// note: usage would be, for example, `character.getSkillName(skill_structure->getSkill(__name__))` instead of `character.getSkillName(i)`

	bool isUntrained();
	int getMaxRanks(int level);

	Skill(std::string name, std::string ability, bool is_general);
	Skill();
	~Skill();
};

// NOTE:
// Rename all variables relating to skills in CharacterClass and ClassData...make them easier to understand
