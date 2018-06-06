#pragma once
#include "stdafx.h"

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
public:
	Item(std::string name, int id, float weight, int cost[4], std::string notes);
	Item();
	~Item();
};

