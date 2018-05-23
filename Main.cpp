#include "stdafx.h"

// Classes
#include "Character.h"
#include "Race.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Skill.h"

// File Formats
#include "FundamentalDataTypes.h"
#include "VCS.h"
#include "RVC.h"
#include "RVR.h"
#include "SkillsFormat.h"

// Other
#include "RaceCreationUtility.h"

void printCharSheet(Character character, CharacterClass char_class, Skill skill[35]); // for debug only

void saveChar(Character character, std::string* err);
void loadChar(Character* character, std::string* err);

void loadClass(CharacterClass* char_class, Character character, std::string* err);
void loadSkill(Skill* skill_ptr, std::string* err);

int main() {

	/*

	Notes:

	This program uses codes for error tracking. A string() function will return an error message.
	string() functions shoud follow this with the proper int() error code.
	int() functions will use 3-digit error codes. The following is a list to describe them:

	First digit:
		0 - type uint8_t, no first digit
		1 - error in "character" class
		2 - error in "item" class
		3 - error in "class" class
		4 - error in combination function/function with friend
	Second digit:
		1 - function not executed
		2 - error in base class
		3 - error in child class
		4 - error in a uint8_t function for RVC
	Third digit:
		9 - bad input

	Additionally, some functions require a 3-character code for execution. This will either be the first three letters of the ability name or the saving throw name. This makes it easier for you when you want to select an attribute rather than trying to remember/find the correct number.
	For example, character.getAbilityScore("str") returns character.strength.

	*/

	Character character;
	CharacterClass char_class;
	Skill skill_structure[35];
	Skill* skill_ptr = &skill_structure[0];

	std::string err;

	std::ifstream charfile;
	charfile.open("Aleksei.vcs", std::ios::in | std::ios::binary);
	if (charfile.is_open()) {
		loadVCS(charfile, &character, &err);
	}
	else {
		std::cerr << "error opening file" << std::endl;
	}

	std::ifstream classfile;
	classfile.open("rogue8.rvc", std::ios::in | std::ios::binary);
	if (classfile.is_open()) {
		loadRVC(classfile, &char_class, character.getLevel(), &err);
	}
	else {
		std::cerr << "error opening file" << std::endl;
	}

	std::ifstream skillfile;
	skillfile.open("skilltest.skills", std::ios::in | std::ios::binary);
	if (skillfile.is_open()) {
		loadSkillStructure(skillfile, skill_ptr, &err);
	}
	else {
		std::cerr << "error opening file" << std::endl;
	}

	charfile.close();
	classfile.close();
	skillfile.close();

	return 0;
}

void printCharSheet(Character character, CharacterClass char_class, Skill skill[35]) {
	std::cout << "character sheet: " << std::endl << std::endl
		<< "Name: \t" << character.getName() << std::endl
		<< "Race: \t" << character.getRace() << std::endl
		<< "Class: \t" << character.getClass() << std::endl
		<< "Level: \t" << (int)character.getLevel() << std::endl
		<< "Max Hit Points: \t" << character.getMaxHitPoints(char_class) << std::endl
		<< "Armor Class: \t" << std::endl
		<< "Base Attack Bonus (M/R): \t" << character.getAttackBonus("mel", char_class) << "/" << character.getAttackBonus("ran", char_class) << std::endl
		<< "Fortitude: \t" << character.getSavingThrow("for", char_class) << std::endl
		<< "Reflex: \t" << character.getSavingThrow("ref", char_class) << std::endl
		<< "Will: \t" << character.getSavingThrow("wil", char_class) << std::endl;
	for (int i = 0; i < 35; i++) {
		std::cout << character.getSkillName(skill[i]) << " skill: \t" << character.getSkillModifier(skill[i]) << std::endl;
	}
	return;
}

void saveChar(Character character, std::string* err) {
	std::ofstream vcs;
	vcs.open(character.getName() + ".vcs", std::ios::out | std::ios::binary);
	if (vcs.is_open()) {
		saveToVCS(vcs, character);
		*err = "file saved successfully as " + character.getName() + ".vcs";
	}
	else {
		*err = "error: could not open file: " + character.getName() + ".vcs";
	}
	return;
}

void loadChar(Character* character, std::string* err) {
	std::string name;
	std::cout << "Character Name? ";
	std::getline(std::cin, name);
	
	std::ifstream vcs;
	vcs.open(name + ".vcs", std::ios::in | std::ios::binary);
	if (vcs.is_open()) {
		loadVCS(vcs, character, err);
	}
	else {
		*err = "error: could not open file: " + name + ".vcs";
	}
}

void loadClass(CharacterClass* char_class, Character character, std::string* err) {
	std::ifstream classfile;
	classfile.open("rogue8.rvc", std::ios::in | std::ios::binary);
	if (classfile.is_open()) {
		loadRVC(classfile, char_class, character.getLevel(), err);
		classfile.close();
	}
	else {
		*err = "error opening file!";
	}
}

void loadSkill(Skill* skill_ptr, std::string* err) {
	std::ifstream loadFile;
	loadFile.open("skilltest.skills", std::ios::in | std::ios::binary);
	if (loadFile.is_open()) {
		loadSkillStructure(loadFile, skill_ptr, err);
		loadFile.close();
	}
	else {
		*err = "could not open file";
	}
}