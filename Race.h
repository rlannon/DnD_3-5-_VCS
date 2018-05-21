#pragma once
#include "stdafx.h"

class Race
{
	std::string race_name;

	int str_bonus;
	int dex_bonus;
	int con_bonus;
	int int_bonus;
	int wis_bonus;
	int cha_bonus;

	friend class Character;
public:
	Race();
	~Race();
};

