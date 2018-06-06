#pragma once
#include "stdafx.h"

/*
Notes about the Item class:

The id code for "Item" is 1xxxx (we have 16 bits so we can go up to 65535)

*/

int getItemID(std::vector<Item> item_vector, std::string name);

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
public:
	std::string getName();
	int getId();

	Item(std::string name, int id, float weight, int cost[4], std::string notes); // this constructor is linked to the Weapon and Armor initializers so we can assign these values in the Weapon and Armor initialization without needing to rewrite the 'Item::name = name' code
	Item();
	~Item();
};

