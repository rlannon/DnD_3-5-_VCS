#pragma once
#include "Item.h"

/*

Notes about the "Armor" class:

Although it is called "Armor", it includes more apparel like clothing, etc.

The id code for items in this class is 31xxx:
	Light Armor:	311xx
	Medium Armor:	312xx
	Heavy Armor:	313xx
	Clothing:		314xx
	Light Shield:	3151x
	Heavy Shield:	3152x
*/

const int no_max_dex = 255; // some items don't have a max dex, so set it to the maximum value for a uin8_t, 255

class Armor :
	public Item
{
	short ac_bonus;
	short max_dex;
	short armor_check_penalty;

	float spell_fail_chance;

	short speed_30;
	short speed_20;

	friend class Character;

	friend void saveToRVO(std::ostream& file, std::vector<Armor> armor);
	friend void loadToVector_RVO(std::istream& file, std::vector<Armor>* armor);
	friend void loadItem_RVO(std::istream& file, Armor* armor, int item_id);

	friend void saveToRVO(std::ostream& file, std::vector<Item> item, std::vector<Weapon> wpn, std::vector<Armor> armor);
	friend void loadToVector_RVO(std::istream& file, std::vector<Item>* item, std::vector<Weapon>* weapon, std::vector<Armor>* armor);
public:
	short getValue(std::string val);
	float getSpellFailChance();

	void newArmor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20);

	Armor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20); // see "Weapon.h" for more information on initializer
	Armor();
	~Armor();
};

