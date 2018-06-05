#pragma once
#include "stdafx.h"
#include "Skill.h"
#include "Spell.h"

/*

ClassData contains all of the data regarding a class at /any given level/. It is not used for a single instance of a player, like CharacterClass is. You use the RVC data to load data from a single level into a CharacterClass instance.

*/

class ClassData
{
	std::string name;

	bool is_caster;

	unsigned short base_attack_bonus[20];

	unsigned short fortitude[20];
	unsigned short reflex[20];
	unsigned short will[20];

	unsigned short hit_die;
	unsigned short skill_coefficient;

	bool classSkillFlag[num_skills];

	unsigned short spells_per_day_by_level[20];
	unsigned short spells_known_by_level[20];
	std::vector<Spell> class_spells;

	friend void createClass(Skill skill_structure[num_skills]);
	friend void modClass(Skill skill_structure[num_skills]);
	friend void loadClassData_RVC(std::istream& file, ClassData* class_obj);
public:
	bool isCaster();

	uint8_t getBaseAttackBonus(int n);
	uint8_t getSavingThrow(std::string s_throw, int n);

	uint8_t getHitDie();
	uint8_t getSkillCoefficient();

	uint8_t getClassSkillFlag(uint8_t n);

	std::string getName();

	uint8_t getSpellsPerDay(int i);
	uint8_t getSpellsKnown(int i);

	uint8_t getVectorSize();
	Spell getSpellFromVector(int i);
	void addSpell(Spell spell);

	ClassData(std::string name, unsigned short bab[20], unsigned short fortitude[20], unsigned short reflex[20], unsigned short will[20], unsigned short hit_die, unsigned short skill_coefficient, bool classSkillFlag[num_skills]);
	ClassData();
	~ClassData();
};