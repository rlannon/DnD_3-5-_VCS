#include "FundamentalDataTypes.h"
#include "VCS.h"
#include "RVO.h"

//using namespace vcs;

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

	// Write inventory vectors to separate rvo file -- char_name.inventory.rvo
	std::ofstream inventory_file;
	inventory_file.open(getDataPath(character.getName() + ".inventory.rvo"), std::ios::out | std::ios::binary);
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

		if (vers == 2) {
			std::ifstream inventory_file;
			inventory_file.open(getDataPath(character->name + ".inventory.rvo"), std::ios::in | std::ios::binary);
			if (inventory_file.is_open()) {
				loadToVector_RVO(inventory_file, &character->char_items, &character->char_wpns, &character->char_armor);
				inventory_file.close();
			}
			else {
				return; // error opening file
			}
		}
		else {
			return; // if file is not version 2, return
		}
	}
	else {
		return;
	}
}

/*

If you wish to ONLY load a VCS, then use loadVCS; however, when we load a character sheet, we want to make sure we load in all of the correct information. Since the "CharacterClass" and "Race" objects in "Character" are POINTERS to objects of these types, we must load to these objects that we are using. When we used "temp = new CharacterClass", the Character object that we were loading had pointers that were pointers to these objects from the function; so, when we used "delete temp" at the end of the function, suddenly all of this information in our Character instance became undefined because we had deleted the objects that "Character::CharacterClass* char_class" and "Character::Race* char_race" were pointing to! So, we make sure we pass in &CharacterClass and &Race into the function so we can load everything correctly.

*/

void loadCharacter(std::istream& vcs_file, Character* character, CharacterClass* char_class, Race* char_race) {
	loadVCS(vcs_file, character);

	std::ifstream rvcfile;
	rvcfile.open(getDataPath(character->char_class_name + ".rvc"), std::ios::in | std::ios::binary);
	if (rvcfile.is_open()) {
		loadRVC(rvcfile, char_class, character->getLevel());
		rvcfile.close();
	}
	else {
		return; // can't load class file, error
	}

	std::ifstream rvrfile;
	rvrfile.open(getDataPath(character->race_name + ".rvr"), std::ios::in | std::ios::binary);
	if (rvrfile.is_open()) {
		loadRVR(rvrfile, char_race);
		rvrfile.close();
	}
	else {
		return; // can't load race file, error
	}

	character->char_class = char_class;
	character->char_race = char_race; // make sure our Character::CharacterClass* and Character::Race* pointers point to these objects we passed in

	return; // done
}