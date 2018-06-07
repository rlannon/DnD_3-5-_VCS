#include "Item.h"

//int getItemID(std::vector<Item> item_vector, std::string name) {
//	for (std::vector<Item>::iterator it = item_vector.begin(); it != item_vector.end(); it++) {
//		if (name == it->getName()) {
//			return it->getId();
//		}
//		else {
//			continue;
//		}
//	}
//}

std::string Item::getName() {
	return Item::name;
}

int Item::getId() {
	return Item::id;
}

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
