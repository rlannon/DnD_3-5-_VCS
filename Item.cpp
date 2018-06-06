#include "Item.h"

Item::Item(std::string name, int id, float weight, int cost[4], std::string notes) {
	Item::name = name;
	Item::id = id;
	Item::weight = weight;
	for (int i = 0; i < 4; i++) {
		Item::cost[i] = cost[i];
	}
	Item::notes = notes;
}

Item::Item()
{
}


Item::~Item()
{
}
