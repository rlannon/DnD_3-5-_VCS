#include "stdafx.h"
#include "Character.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Skill.h"
#include "RVC.h"

void printCharSheet(Character character, CharacterClass char_class, Skill skill); // for debug only

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

	Skill skills[35]{
		Skill("Appraise", "int", 1),
		Skill("Balance", "dex", 1),
		Skill("Bluff", "cha", 1),
		Skill("Climb", "str", 1),
		Skill("Concentration", "con", 1),
		Skill("Craft", "int", 1),
		Skill("Decipher Script", "int", 1),
		Skill("Diplomacy", "cha", 1),
		Skill("Disable Device", "int", 1),
		Skill("Disguise", "cha", 1),
		Skill("Escape Artist", "dex", 1),
		Skill("Forgery", "int", 1),
		Skill("Gather Information", "int", 1),
		Skill("Handle Animal", "cha", 1),
		Skill("Heal", "wis", 1),
		Skill("Hide", "dex", 1),
		Skill("Intimidate", "cha", 1),
		Skill("Jump", "str", 1),
		Skill("Knowledge", "int", 1),
		Skill("Listen", "wis", 1),
		Skill("Move Silently", "dex", 1),
		Skill("Open Lock", "dex", 0),
		Skill("Perform", "cha", 0),
		Skill("Profession", "wis", 1),
		Skill("Ride", "dex", 1),
		Skill("Search", "int", 1),
		Skill("Sense Motive", "wis", 1),
		Skill("Sleight of Hand", "dex", 1),
		Skill("Spellcraft", "int", 0),
		Skill("Spot", "wis", 1),
		Skill("Survival", "wis", 1),
		Skill("Swim", "str", 1),
		Skill("Tumble", "dex", 1),
		Skill("Use Magic Device", "int", 0),
		Skill("Use Rope", "dex", 1)
	};

	std::string err = "";

	// this is mostly for dummy stuff
	bool flags[35] = { 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1 };
	unsigned short bab_mid[20] = { 0,1,2,3,3,4,5,6,6,7,8,9,9,10,11,12,12,13,14,15 };
	unsigned short save_low[20] = { 0,0,1,1,1,2,2,2,3,3,3,4,4,4,5,5,5,6,6,6, };
	unsigned short save_high[20] = { 2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,10,10,11,11,12 };

	ClassData rogue8("Rogue", bab_mid, save_low, save_high, save_low, 6, 8, flags);

	std::ofstream outfile;
	outfile.open("rogue8.rvc", std::ios::out | std::ios::binary);
	if (outfile.is_open()) {
		saveClassStructure(outfile, rogue8);
		outfile.close();
	}
	else {
		std::cout << "error opening file!" << std::endl;
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

	return 0;
}

void printCharSheet(Character character, CharacterClass char_class, Skill skill) {
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

	std::cout << character.getSkillName(skill) << " skill: \t" << character.getSkillModifier(skill);
	return;
}