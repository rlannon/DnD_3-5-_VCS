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
void loadItem_RVO(std::istream& file, Item* item, int item_id) {
	short type;
	int id = 0;
	if (readHeader(file)) {
		// check to make sure we are using the correct type
		type = readU8(file);

		if (type == obj_is_item) {
			int num_items = (int)readU16(file);
			
			for (int i = 0; i < num_items; i++) {
				// the first data is our item id
				id = readU16(file);
				if (item_id == id) {
					// if we have the right item id, get the object
					item->id = id;
					item->name = readString(file);
					item->weight = convertU32(readU32(file));

					for (int i = 0; i < 4; i++) {
						item->cost[i] = readU16(file);
					}

					item->notes = readString(file);

					break; // we are done, no need to finish the loop
				}
				else {
					if (i != (num_items - 1)) { // make sure we don't read past the end of the file
						/*

						Because we skip ahead to the next item before we increment, we cannot skip ahead once we are on the last item -- so DO NOT skip ahead if we increment up to the last item. This allows us to read the last item in the vector, but it won't check once it reaches it.
						Say num_items = 3:
							i = 0
							Read first item
							Skip ahead From item 0 to item 1

							i = 1
							Read second item
							Skip ahead from item 1 to item 2

							i = 2
							Read third item
							Now, i = num_items - 1 (3 - 1 = 2), so do not continue to read, and break instead; if we try to read ahead, we will go past the end of the file which is a very bad thing, and we won't catch that we have read too far until we get back to the top of the loop, by which point we have already tried to access items past the end of the file.

						This is why we compare against num_items - 1, not against num_items

						*/
						// read ahead to the next object
						int str_len = readU16(file); // get the "name" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string

						file.seekg(4, std::ios::cur); // skip ahead 4 bytes past (U32)weight
						file.seekg(8, std::ios::cur); // skip ahead 8 bytes past (U16)cost (4)

						str_len = readU16(file); // get the "notes" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string
						// now, we should be at the next id field
					}
					else if (i == (num_items - 1)) {
						break;
					}
				}
			}
		}
	}
	else { // incorrect file format
		return;
	}
}
void loadItem_RVO(std::istream& file, Weapon* weapon, int item_id) {
	short type;
	int id = 0;
	if (readHeader(file)) {
		type = readU8(file);

		if (type == obj_is_weapon) {
			// get the number of items in the file
			int num_items = readU16(file);

			for (int i = 0; i < num_items; i++) {
				// the first data is our item id
				id = readU16(file);
				if (item_id == id) {
					// if we have the right item id, get the object

					// first, get Item data
					weapon->id = id;
					weapon->name = readString(file);
					weapon->weight = convertU32(readU32(file));

					for (int i = 0; i < 4; i++) {
						weapon->cost[i] = readU16(file);
					}

					weapon->notes = readString(file);

					// then, get Weapon-specific data

					weapon->damage_s = readU8(file);
					weapon->damage_m = readU8(file);
					weapon->critical = readU8(file);
					weapon->range = readU8(file);

					weapon->type = readString(file);

					break; // we are done, no need to finish the loop
				}
				else {
					if (i != (num_items - 1)) { // make sure we don't read past the end of the file
												// see loadItem_RVO(item) for the explanation
						// read Item data
						int str_len = readU16(file); // get the "name" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string

						file.seekg(4, std::ios::cur); // skip ahead 4 bytes past (U32)weight
						file.seekg(8, std::ios::cur); // skip ahead 8 bytes past (U16)cost (4)

						str_len = readU16(file); // get the "notes" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string

						// skip past weapon data

						file.seekg(4, std::ios::cur); // skip past weapon numerical data
						// skip past weapon type
						str_len = readU16(file);
						file.seekg(str_len, std::ios::cur);
					}
					else if (i == (num_items - 1)) {
						break;
					}
				}
			}
		}
		else { // object is wrong type
			return;
		}
	}
	else { // incorrect file format
		return;
	}
}
void loadItem_RVO(std::istream& file, Armor* armor, int item_id) {
	short type;
	int id = 0;
	if (readHeader(file)) {
		// check to make sure we are using the correct type
		type = readU8(file);

		if (type == obj_is_armor) {
			int num_items = (int)readU16(file);

			for (int i = 0; i < num_items; i++) {
				// the first data is our item id
				id = readU16(file);
				if (item_id == id) {
					// if we have the right item id, get the object
					armor->id = id;
					armor->name = readString(file);
					armor->weight = convertU32(readU32(file));

					for (int i = 0; i < 4; i++) {
						armor->cost[i] = readU16(file);
					}

					armor->notes = readString(file);

					// armor-specific data
					armor->ac_bonus = readU8(file);
					armor->max_dex = readU8(file);
					armor->armor_check_penalty = readU8(file);

					armor->spell_fail_chance = convertU8(readU8(file));

					armor->speed_30 = readU8(file);
					armor->speed_20 = readU8(file);

					break; // we are done, no need to finish the loop
				}
				else {
					if (i != (num_items - 1)) { // make sure we don't read past the end of the file
												// See loadItem_RVO(item) for explanation
						int str_len = readU16(file); // get the "name" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string

						file.seekg(4, std::ios::cur); // skip ahead 4 bytes past (U32)weight
						file.seekg(8, std::ios::cur); // skip ahead 8 bytes past (U16)cost (4)

						str_len = readU16(file); // get the "notes" string length
						file.seekg(str_len, std::ios::cur); // skip ahead past the string

						// skip past rest of armor-specific data
						file.seekg(6, std::ios::cur);
					}
					else if (i == (num_items - 1)) {
						break;
					}
				}
			}
		}
	}
	else { // incorrect file format
		return;
	}
}