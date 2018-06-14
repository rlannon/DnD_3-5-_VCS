#pragma once
#include "stdafx.h"

/*
Notes about the Item class:

The id code for "Item" is 1xxxx (we have 16 bits so we can go up to 65535)

*/

class Item
{
protected:
	std::string name;
	int id;
	float weight;
	int cost[4]; // 0 = cp, 1 = sp, 2 = gp, 3 = pp
	std::string notes;

	friend void writeItemData(std::ostream& file, Item item);
	friend void readItemData(std::istream& file, Item* item);

	friend void loadItem_RVO(std::istream& file, Item* item, int item_id);

	friend class Weapon; // need these for the loadToVector_RVO(file, item, weapon armor) -- otherwise the code breaks
	friend class Armor;
	friend void saveToRVO(std::ostream& file, std::vector<Item> item, std::vector<Weapon> wpn, std::vector<Armor> armor);
	friend void loadToVector_RVO(std::istream& file, std::vector<Item>* item, std::vector<Weapon>* weapon, std::vector<Armor>* armor);
public:
	std::string getName();
	int getId();

	Item(std::string name, int id, float weight, int cost[4], std::string notes); // this constructor is linked to the Weapon and Armor initializers so we can assign these values in the Weapon and Armor initialization without needing to rewrite the 'Item::name = name' code
	Item();
	~Item();
};

