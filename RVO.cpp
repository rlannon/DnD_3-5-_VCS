#include "RVO.h"
#include "FundamentalDataTypes.h"

// functions to make our lives easier / the code easier to read

void writeHeader(std::ostream& file) {
	char * header = "RVOf";
	file.write(header, 4);

	writeU8(file, rvo_version);
}

void writeItemData(std::ostream& file, Item item) {
	writeU16(file, item.id);

	writeString(file, item.name);
	writeU32(file, convertFloat_U32(item.weight));

	writeU16(file, item.cost[0]);
	writeU16(file, item.cost[1]);
	writeU16(file, item.cost[2]);
	writeU16(file, item.cost[3]);

	writeString(file, item.notes);
}

bool readHeader(std::istream& file) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	file.read(buffer, 4);

	// first, check our header data to make sure it is the correct file format. If so, continue on
	if (header[0, 1, 2, 3] == *"R", "V", "O", "f") {
		vers = readU8(file);
		return true;
	}
	else {
		return false;
	}
}

void readItemData(std::istream& file, Item* item) {
	item->id = readU16(file);

	item->name = readString(file);
	item->weight = convertU32(readU32(file));

	item->cost[0] = readU16(file);
	item->cost[1] = readU16(file);
	item->cost[2] = readU16(file);
	item->cost[3] = readU16(file);

	item->notes = readString(file);
}

// save vector to RVO

void saveToRVO(std::ostream& file, std::vector<Item> item) {
	writeHeader(file);

	writeU8(file, obj_is_item);
	writeU16(file, item.size());

	for (std::vector<Item>::iterator it = item.begin(); it != item.end(); it++) {
		writeItemData(file, *it);
	}
}
void saveToRVO(std::ostream& file, std::vector<Weapon> weapon) {
	writeHeader(file);

	writeU8(file, obj_is_weapon);
	writeU16(file, weapon.size());

	for (std::vector<Weapon>::iterator it = weapon.begin(); it != weapon.end(); it++) {
		writeItemData(file, *it);
		// weapon-specific data
		writeU8(file, it->damage_s);
		writeU8(file, it->damage_m);
		writeU8(file, it->critical);
		writeU8(file, it->range);

		writeString(file, it->type);
	}
}
void saveToRVO(std::ostream& file, std::vector<Armor> armor) {
	writeHeader(file);

	writeU8(file, obj_is_armor);
	writeU16(file, armor.size());

	for (std::vector<Armor>::iterator it = armor.begin(); it != armor.end(); it++) {
		writeItemData(file, *it);
		// armor-specific data
		writeU8(file, it->ac_bonus);
		writeU8(file, it->max_dex);
		writeU8(file, it->armor_check_penalty);

		writeU8(file, convertFloat_U8(it->spell_fail_chance));

		writeU8(file, it->speed_30);
		writeU8(file, it->speed_20);
	}
}

// load from RVO format to vector
void loadToVector_RVO(std::istream& file, std::vector<Item>* item) {
	short type;
	if (readHeader(file)) {
		type = readU8(file);
		if (type == obj_is_item) {
			Item temp;
			int num_items = readU16(file);

			for (int i = 0; i < num_items; i++) {
				readItemData(file, &temp);
				item->push_back(temp);
			}
		}
	}
	else { // incorrect file format
		return;
	}
}
void loadToVector_RVO(std::istream& file, std::vector<Weapon>* weapon) {
	short type;
	if (readHeader(file)) {
		type = readU8(file);
		if (type == obj_is_weapon) {
			Weapon temp;
			int num_items = readU16(file);

			for (int i = 0; i < num_items; i++) {
				readItemData(file, &temp);

				// weapon-specific data
				temp.damage_s = readU8(file);
				temp.damage_m = readU8(file);
				temp.critical = readU8(file);
				temp.range = readU8(file);

				temp.type = readString(file);
				
				// finally, push to our vector
				weapon->push_back(temp);
			}
		}
	}
	else { // incorrect file format
		return;
	}
}
void loadToVector_RVO(std::istream& file, std::vector<Armor>* armor) {
	short type;
	if (readHeader(file)) {
		type = readU8(file);
		if (type == obj_is_armor) {
			Armor temp;
			int num_items = readU16(file);

			for (int i = 0; i < num_items; i++) {
				readItemData(file, &temp);

				// armor-specific data
				temp.ac_bonus = readU8(file);
				temp.max_dex = readU8(file);
				temp.armor_check_penalty = readU8(file);

				temp.spell_fail_chance = convertU8(readU8(file));

				temp.speed_30 = readU8(file);
				temp.speed_20 = readU8(file);

				// finally, push to vector
				armor->push_back(temp);
			}
		}
	}
	else { // incorrect file format
		return;
	}
}

// load individual object from RVO
void loadItem_RVO(std::istream& file, Item* item) {

}
void loadItem_RVO(std::istream& file, Weapon* weapon) {

}
void loadItem_RVO(std::istream& file, Armor* armor) {

}