#pragma once
#include "Item.h"

/*

Notes about the "Weapon" class:

The id code for items in this class is 21xxx

*/

class Weapon :
	public Item
{
	short damage_s;
	short damage_m;
	short critical;
	short range;

	std::string type;

	friend class Character;

	friend void saveToRVO(std::ostream& file, std::vector<Weapon> weapon);
	friend void loadToVector_RVO(std::istream& file, std::vector<Weapon>* weapon);

	friend void loadItem_RVO(std::istream& file, Weapon* weapon, int item_id);

	friend void saveToRVO(std::ostream& file, std::vector<Item> item, std::vector<Weapon> wpn, std::vector<Armor> armor);
	friend void loadToVector_RVO(std::istream& file, std::vector<Item>* item, std::vector<Weapon>* weapon, std::vector<Armor>* armor);
public:
	Weapon(std::string name, int id, float weight, int cost[4], std::string notes, short damage_s, short damage_m, short critical, short range, std::string type); // this initializer is linked to the Item initializer in the file 'Weapon.cpp', so our values for name, id, weight, cost, and notes automatically get initialized through the Item() initialization; we don't need to write code for it in the Weapon initializer
	Weapon();
	~Weapon();
};
