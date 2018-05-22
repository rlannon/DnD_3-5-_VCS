#pragma once
#include "stdafx.h"

class Race
{
	std::string name;

	int str_bonus;
	int dex_bonus;
	int con_bonus;
	int int_bonus;
	int wis_bonus;
	int cha_bonus;

	std::string known_languages;

	// allow Character access to these private members
	friend class Character;

	// allow our file format to modify this data
	friend void saveToRVR(std::ostream& file, Race race);
	friend void loadRVR(std::istream& file, Race* race, std::string* err);
	friend void saveToVCS(std::ostream& file, Character character);
public:
	Race(std::string name, int str_bonus, int dex_bonus, int con_bonus, int int_bonus, int wis_bonus, int cha_bonus, std::string lang);
	Race();
	~Race();
};

