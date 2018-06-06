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

// debug function
void printCharSheet(Character character, CharacterClass char_class, Skill skill[num_skills]);

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

	std::ifstream racefile;
	racefile.open("data/Dwarf.rvr", std::ios::in | std::ios::binary);
	if (racefile.is_open()) {
		loadRVR(racefile, &char_race);
		racefile.close();
	}
	else {
		err += "error reading file \"data/human.rvr\"!\n";
	}

	std::ifstream classfile;
	classfile.open("data/test.rvc", std::ios::in | std::ios::binary);
	if (classfile.is_open()) {
		loadRVC(classfile, &char_class, 0);
		std::cout << "Test file is version: " << getFileVersion(classfile) << std::endl;
		classfile.close();
	}
	else {
		err += "error reading file \"data/rogue.rvc\"!\n";
	}

	std::ifstream skillfile;
	skillfile.open("data/skills.skills", std::ios::in | std::ios::binary);
	if (skillfile.is_open()) {
		loadSkillStructure(skillfile, skill_ptr);
		skillfile.close();
	}
	else {
		err += "error reading file \"data/skills.skills\"!\n";
	}

	while (n > 0) {
		std::cout << "Select an option:\n" << std::endl
			<< "[1] Use Utility" << std::endl
			<< "[2] Print CharSheet" << std::endl
			<< "[3] Load Test Class" << std::endl
			<< "\n[4] Quit" << std::endl;
		std::cin >> c;
		switch (c) {
		case 1:
			utility();
			break;
		case 2:
			character.createNewCharacter(&char_class, &char_race, skill_ptr, "Stout", 10, 11, 12, 13, 14, 15);
			printCharSheet(character, char_class, skill_structure);
			break;
		case 3:
			classfile.open("data/test.rvc", std::ios::in | std::ios::binary);
			if (classfile.is_open()) {
				loadRVC(classfile, &char_class, 15);

				std::cout << "file version: " << getFileVersion(classfile) << std::endl;

				classfile.close();
			}
			else {
				err += "error reading file!\n";
			}
			break;
		case 4:
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

void printCharSheet(Character character, CharacterClass char_class, Skill skill[num_skills]) {
	std::cout << "character sheet: " << std::endl << std::endl
		<< "Name: \t" << character.getName() << std::endl
		<< "Race: \t" << character.getRace() << std::endl
		<< "Class: \t" << character.getClass() << std::endl
		<< "Level: \t" << (int)character.getLevel() << std::endl
		<< "Strength: \t" << character.getAbilityScore("str") << std::endl
		<< "Max Hit Points: \t" << character.getMaxHitPoints() << std::endl
		<< "Armor Class: \t" << std::endl
		<< "Base Attack Bonus (M/R): \t" << character.getAttackBonus("mel") << "/" << character.getAttackBonus("ran") << std::endl
		<< "Fortitude: \t" << character.getSavingThrow("for") << std::endl
		<< "Reflex: \t" << character.getSavingThrow("ref") << std::endl
		<< "Will: \t" << character.getSavingThrow("wil") << std::endl << std::endl;
	// list class skills
	short count = 0;
	for (int i = 0; i < character.getNumSkills(); i++) {
		std::cout << character.getSkill(i).getSkillName() << ": " << character.getSkillModifier(character.getSkill(i)) << std::endl;
		count++;
	}
	std::cout << "num skills: " << count << std::endl;

	return;
}