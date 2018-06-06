#pragma once
#include "Item.h"

class Weapon :
	public Item
{
	short damage_s;
	short damage_m;
	short critical;
	short range;

	std::string type;

	friend void saveToRVO(std::ostream& file, std::vector<Weapon> weapon);
	friend void loadToVector_RVO(std::istream& file, std::vector<Weapon>* weapon);
public:
	Weapon(std::string name, int id, float weight, int cost[4], std::string notes, short damage_s, short damage_m, short critical, short range, std::string type);
	Weapon();
	~Weapon();
};

