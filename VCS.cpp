#include "FundamentalDataTypes.h"
#include "VCS.h"
#include "RVO.h"

void saveToVCS(std::ostream& file, Character character) {
	// write file header
	char * header = "v35VCSf";
	file.write(header, 7);
	writeU8(file, vcs_version);

	// write data as specified in VCS.h
	writeString(file, character.getName());
	writeString(file, character.getRace());
	writeString(file, character.getClass());

	writeU16(file, (uint16_t)character.xp);

	writeU8(file, (uint8_t)character.getAbilityScore("str"));
	writeU8(file, (uint8_t)character.getAbilityScore("dex"));
	writeU8(file, (uint8_t)character.getAbilityScore("con"));
	writeU8(file, (uint8_t)character.getAbilityScore("int"));
	writeU8(file, (uint8_t)character.getAbilityScore("wis"));
	writeU8(file, (uint8_t)character.getAbilityScore("cha"));

	writeU8(file, (uint8_t)character.initiative_mod);

	writeU16(file, (uint16_t)character.money[0]); // cp
	writeU16(file, (uint16_t)character.money[1]); // sp
	writeU16(file, (uint16_t)character.money[2]); // gp
	writeU16(file, (uint16_t)character.money[3]); // pp

	// NEW IN VERSION 2

	// write inventory vectors as RVO format here
	std::ofstream inventory_file;
	inventory_file.open(character.getClass() + ".inventory.rvo", std::ios::out | std::ios::binary);
	if (inventory_file.is_open()) {
		saveToRVO(inventory_file, character.char_items, character.char_wpns, character.char_armor);
		inventory_file.close();
	}
	else {
		return; // error opening file
	}
}

void loadVCS(std::istream& file, Character* character) {
	char header[7];
	char * buffer = &header[0];
	short vers;

	file.read(buffer, 7);

	// if we have the correct format, load to the class
	if (header[0, 1, 2, 3, 4, 5, 6] == *"v", "3", "5", "V", "C", "S", "f") {
		// load version
		vers = readU8(file);

		// read strings
		character->name = readString(file);
		character->race_name = readString(file);
		character->char_class_name = readString(file);

		// read xp
		character->xp = readU16(file);

		// read abilities
		character->strength = readU8(file);
		character->dexterity = readU8(file);
		character->constitution = readU8(file);
		character->intelligence = readU8(file);
		character->wisdom = readU8(file);
		character->charisma = readU8(file);

		character->initiative_mod = readU8(file);

		// read money
		character->money[0] = readU16(file); // cp
		character->money[1] = readU16(file); // sp
		character->money[2] = readU16(file); // gp
		character->money[3] = readU16(file); // pp

		if (vers == 1) {
			return; // version one files do not save or load inventory data
		}
		else if (vers == 2) {
			std::ifstream inventory_file;
			inventory_file.open(character->char_class_name + ".inventory.rvo", std::ios::in | std::ios::binary);
			if (inventory_file.is_open()) {
				loadToVector_RVO(inventory_file, &character->char_items, &character->char_wpns, &character->char_armor);
				inventory_file.close();
			}
			else {
				return; // error opening file
			}
		}
	}
	else {
		return;
	}
}