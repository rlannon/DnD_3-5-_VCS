#pragma once
#include "stdafx.h"

/*

ClassData contains all of the data regarding a class at /any given level/. It is not used for a single instance of a player, like CharacterClass is. You use the RVC data to load data from a single level into a CharacterClass instance.

*/

class ClassData
{
	std::string name;

	unsigned short base_attack_bonus[20];

	unsigned short fortitude[20];
	unsigned short reflex[20];
	unsigned short will[20];

	unsigned short hit_die;
	unsigned short skill_coefficient;

	bool classSkillFlag[35];
public:
	uint8_t getBaseAttackBonus(int n);
	uint8_t getSavingThrow(std::string s_throw, int n);

	uint8_t getHitDie();
	uint8_t getSkillCoefficient();

	uint8_t getClassSkillFlag(uint8_t n);

	std::string getName();

	ClassData(std::string name, unsigned short bab[20], unsigned short fortitude[20], unsigned short reflex[20], unsigned short will[20], unsigned short hit_die, unsigned short skill_coefficient, bool classSkillFlag[35]);
	~ClassData();
};