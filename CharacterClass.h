#pragma once
#include "stdafx.h"

/*

	The purpose of this class is to define everything about the character's class. An instance of CharacterClass should /directly/ correspond to an instance of Character. This will keep class information separate from the player's character sheet. However, because Character is a friend of CharacterClass, we can directly load data from 
	
	There are two classes relating to a character's class -- CharacterClass and ClassData. CharacterClass, this class, contains all of the data about the player's class *at their current level*. This is the struct that Character talks to in order to make calculations. It maps 1:1 with a single player object.

*/

class CharacterClass
{
	std::string name;

	unsigned short base_attack_bonus;

	unsigned short fortitude;
	unsigned short reflex;
	unsigned short will;

	unsigned short hit_die; // seed number for PRNG, if we decide to use it -- dx, where x == hit_die

	unsigned short skill_coefficient;

	// our voids to set player data, used in loadClassData()
	// listed here in the order they appear in the RVC function
	void setBaseAttackBonus(uint8_t val);
	void setSavingThrow(std::string s_throw, uint8_t val);
	void setHitDie(uint8_t val);
	void setSkillCoefficient(uint8_t val);
	void setClassSkillFlag(bool skill[35]); // set a specific skill flag
	void setName(std::string str);

	bool classSkillFlag[35]; // flags to tell us if a skill is a class skill or not
	// for skill flags -- look on D&D SRD 3.5e -- follows Skill class exactly

	friend class Character; // allow class "Character" to access these private members
	friend class Skill; // allow class 'Skill' to access these private members
	friend void loadClassData(std::istream& file, CharacterClass* class_obj, uint8_t level, std::string* err);
public:
	
	/*

	// These are in ClassData because they are used in the save function
	// So we probably..don't need them...I don't think they're used anywhere else

	uint16_t getBaseAttackBonus();
	uint8_t getSavingThrow(std::string s_throw);
	uint8_t getHitDie();
	std::string getName();

	*/

	CharacterClass(std::string name,  short base_attack_bonus, unsigned short fortitude, unsigned short reflex, unsigned short will, unsigned short hit_die, unsigned short skill_coefficient);
	~CharacterClass();
};