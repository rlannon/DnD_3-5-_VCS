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
public:
	uint8_t getLevel();

	std::string getValue(std::string value);

	Spell(std::string name, std::string associated_class, uint8_t spell_level, std::string components, std::string casting_time, std::string range, std::string target, std::string duration, std::string saving_throw, bool spell_resistance);
	Spell();
	~Spell();
};

