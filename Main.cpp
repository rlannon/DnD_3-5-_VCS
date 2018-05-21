#include "stdafx.h"

// Classes
#include "Character.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Skill.h"

// File Formats
#include "FundamentalDataTypes.h"
#include "RVC.h"
#include "SkillsFormat.h"

void printCharSheet(Character character, CharacterClass char_class, Skill skill[35]); // for debug only

int main() {

	/*

	Notes:

	This program uses codes for error tracking. A char() or string() function will return "err" or "!".
	string() functions will follow this with the proper int() error code. char() functions will be avoided.
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

	Character new_char("Aleksei", "Taer", "Rogue", 10, 11, 12, 13, 14, 15);
	CharacterClass new_class("", 0, 0, 0, 0, 0, 0);

	Skill test_skill[35];
	Skill* skill_ptr = test_skill;

	std::string err = "";

	std::ifstream loadFile;
	loadFile.open("skilltest.skills", std::ios::in | std::ios::binary);
	if (loadFile.is_open()) {
		loadSkillStructure(loadFile, skill_ptr, &err);
		loadFile.close();
	}
	else {
		err = "could not open file";
	}

	std::ifstream infile;
	infile.open("rogue8.rvc", std::ios::in | std::ios::binary);
	if (infile.is_open()) {
		loadClassData(infile, &new_class, new_char.getLevel(), &err);
		infile.close();
	}
	else {
		std::cout << "error opening file!" << std::endl;
	}
	printCharSheet(new_char, new_class, test_skill);

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