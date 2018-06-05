#pragma once
#include "stdafx.h"

class Spell
{
	std::string name;
	std::string associated_class;
	
	uint8_t spell_level;

	std::string components;
	std::string casting_time;
	std::string range;
	std::string target;
	std::string duration;
	std::string saving_throw;

	bool spell_resistance;
	
	std::string description;

	friend class CharacterClass;
	friend class ClassData;
	friend void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);
	friend void loadClassData_RVC(std::istream& file, ClassData* class_obj);
	friend void addSpells();
public:
	uint8_t getLevel();
	bool spellResistance();
	std::string getValue(std::string value);

	void setValue(std::string name, std::string new_value);

	Spell(std::string name, std::string associated_class, uint8_t spell_level, std::string components, std::string casting_time, std::string range, std::string target, std::string duration, std::string saving_throw, bool spell_resistance);
	Spell();
	~Spell();
};

