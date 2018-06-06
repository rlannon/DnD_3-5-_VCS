#pragma once
#include "Item.h"

class Armor :
	public Item
{
	short ac_bonus;
	short max_dex;
	short armor_check_penalty;

	float spell_fail_chance;

	short speed_30;
	short speed_20;

	friend void saveToRVO(std::ostream& file, std::vector<Armor> armor);
	friend void loadToVector_RVO(std::istream& file, std::vector<Armor>* armor);
public:
	Armor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20);
	Armor();
	~Armor();
};

