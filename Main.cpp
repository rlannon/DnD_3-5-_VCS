#include "stdafx.h"

// Classes
#include "Character.h"
#include "Race.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Skill.h"
#include "Spell.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

// File Formats
#include "FundamentalDataTypes.h"
#include "VCS.h"
#include "RVO.h"
#include "RVC.h"
#include "RVR.h"
#include "SkillsFormat.h"

// Other
#include "Utility.h"

int main() {
	/*

	Notes:

	This program uses codes for error tracking. A string() function will return an error message.
	string() functions shoud follow this with the proper int() error code.
	int() and uint8_t() functions will use 3-digit error codes. The following is a list to describe them:

	First digit:
		0 - type uint8_t, no first digit
		1 - error in "character" class
		2 - error in "item" class
		3 - error in "class" class
		4 - error in combination function/function with friend
		5 - error in file load method
	Second digit:
		1 - function not executed
		2 - error in base class
		3 - error in child class
		4 - error in a uint8_t function for RVC
	Third digit:
		8 - incorrect file header
		9 - bad input

	Additionally, some functions require a code for execution. The functions use strings, so you can use the 3-character code (the old way) OR the full name -- for example,
			character.getAbilityScore("str")
		and
			character.getAbilityScore("strength")
		are both acceptable. Note the full names and the three-letter codes ALWAYS use lowercase.

	*/

	Character character;
	Race char_race;
	CharacterClass char_class;
	Skill skill_structure[num_skills];
	Skill* skill_ptr = &skill_structure[0];

	Spell new_spell("Blindness/Deafness", "Bard, Cleric, Sorcerer/Wizard", 2, "V", "1 standard action", "Medium (100 ft + 10 ft/level)", "One living creature", "Permanent (D)", "Fortitude negates", true);

	Spell char_spell;

	ClassData temp_data;

	std::string err = "";

	int c;
	uint8_t n = 1;
	/*
	std::ifstream racefile;
	racefile.open(getDataPath("Dwarf.rvr"), std::ios::in | std::ios::binary);
	if (racefile.is_open()) {
		loadRVR(racefile, &char_race);
		racefile.close();
	}
	else {
		err += "error reading file \"data/human.rvr\"!\n";
	}

	std::ifstream classfile;
	classfile.open(getDataPath("Barbarian.rvc"), std::ios::in | std::ios::binary);
	if (classfile.is_open()) {
		loadRVC(classfile, &char_class, 0);
		classfile.close();
	}
	else {
		err += "error reading file \"data/rogue.rvc\"!\n";
	}

	std::ifstream skillfile;
	skillfile.open(getDataPath("skills.skills"), std::ios::in | std::ios::binary);
	if (skillfile.is_open()) {
		loadSkillStructure(skillfile, skill_ptr);
		skillfile.close();
	}
	else {
		err += "error reading file \"data/skills.skills\"!\n";
	}
	*/
	//character.createNewCharacter(&char_class, &char_race, skill_ptr, "Stout", 10, 11, 12, 13, 14, 15);
	
	/*
	int cost[4] = { 1, 2, 3, 4 };
	Weapon wpn("test", 1, 2, cost, "none", 1, 2, 3, 4, "some type");
	Armor armor("sample", 3, 4, cost, "something", 5, 6, 7, .8, 30, 20);
	Item item("an item", 5, 6, cost, "notes!!");

	character.createNewCharacter(&char_class, &char_race, skill_ptr, "Stout", 10, 11, 12, 13, 14, 15);

	character.addItem(wpn);
	character.addItem(armor);
	character.addItem(item);
	
	std::ofstream charfile;
	charfile.open("sample.vcs", std::ios::out | std::ios::binary);
	if (charfile.is_open()) {
		saveToVCS(charfile, character);
		charfile.close();
	}
	else {
		std::cout << "vcs err" << std::endl;
	}

	Character test_char;

	std::ifstream samplefile;
	samplefile.open("sample.vcs", std::ios::in | std::ios::binary);
	if (samplefile.is_open()) {
		loadVCS(samplefile, &test_char);
		samplefile.close();
	}
	else {
		std::cout << "vcs load err" << std::endl;
	}*/

	std::ofstream vcsfile;
	std::ifstream in_vcs;

	while (n > 0) {
		std::string in_data;
		std::cout << "Select an option:\n" << std::endl
			<< "[1] Use Utility" << std::endl
			<< "[2] Create Character" << std::endl
			<< "[3] Save Character as VCS" << std::endl
			<< "[4] Load VCS to Character" << std::endl
			<< "\n[5] Quit" << std::endl;
		std::cin >> c;
		switch (c) {
		case 1:
			utility();
			break;
		case 2:
			break;
		case 3:
			vcsfile.open(getDataPath(character.getName() + ".vcs"), std::ios::out | std::ios::binary);
			if (vcsfile.is_open()) {
				saveToVCS(vcsfile, character);
				vcsfile.close();
			}
			else {
				std::cout << "could not open vcs file" << std::endl;
			}
			break;
		case 4:
			in_vcs.open("data/Stout.vcs", std::ios::in | std::ios::binary);
			if (in_vcs.is_open()) {
				loadCharacter(in_vcs, &character, &char_class, &char_race);
				in_vcs.close();
			}
			else {
				std::cout << "could not open vcs file" << std::endl;
			}
			break;
		case 5:
			n--;
			break;
		default:
			std::cout << "invalid selection!" << std::endl;
			break;
		}
		std::cout << std::endl;
	}
	return 0;
}