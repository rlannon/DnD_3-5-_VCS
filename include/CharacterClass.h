#pragma once
#include "stdafx.h"
#include "Skill.h"
#include "Spell.h"

/*

	The purpose of this class is to define everything about the character's class. An instance of CharacterClass should /directly/ correspond to an instance of Character. This will keep class information separate from the player's character sheet. However, because Character is a friend of CharacterClass, we can directly load data from 
	
	There are two classes relating to a character's class -- CharacterClass and ClassData. CharacterClass, this class, contains all of the data about the player's class *at their current level*. This is the struct that Character talks to in order to make calculations. It maps 1:1 with a single player object.

*/

class CharacterClass
{
	std::string name;

	bool is_caster;

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

	void setName(std::string str);

	std::vector<Skill> class_skill_vector;

	// magic
	short spells_per_day;
	short spells_known;
	// our spells vector -- containing spells the class may use or learn
	std::vector<Spell> class_spells;


	friend class Character; // allow class "Character" to access these private members
	friend class Skill; // allow class 'Skill' to access these private members
	friend void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);
public:
	Spell getSpell(std::string spell_name); // get spell by name
	std::vector<Spell> getSpell(int level); // used for adding all spells of a particular vector

	CharacterClass(std::string name,  short base_attack_bonus, unsigned short fortitude, unsigned short reflex, unsigned short will, unsigned short hit_die, unsigned short skill_coefficient);
	CharacterClass();
	~CharacterClass();
};