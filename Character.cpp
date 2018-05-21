#include "stdafx.h"
#include "Character.h"
#include "CharacterClass.h"

std::string Character::getName() {
	return Character::name;
}

std::string Character::getRace() {
	return Character::race;
}

std::string Character::getClass() {
	return Character::character_class;
}

int Character::getMaxHitPoints(CharacterClass char_class) {
	return (Character::level * (Character::getModifier(Character::getAbilityScore("con")) + char_class.hit_die));
}

int Character::getModifier(int ability_score) {
	return ((ability_score - 10) / 2);
}

int Character::getAbilityScore(std::string ability) {
	if (ability == "str") {
		return Character::strength;
	}
	else if (ability == "con") {
		return Character::constitution;
	}
	else if (ability == "dex") {
		return Character::dexterity;
	}
	else if (ability == "int") {
		return Character::intelligence;
	}
	else if (ability == "wis") {
		return Character::wisdom;
	}
	else if (ability == "cha") {
		return Character::charisma;
	}
 	else {
		return 119;
	}
}

int Character::getSavingThrow(std::string s_throw, CharacterClass char_class) {
	if (s_throw == "for") {
		return Character::getModifier(Character::constitution) + char_class.fortitude;
	}
	else if (s_throw == "ref") {
		return Character::getModifier(Character::dexterity) + char_class.reflex;
	}
	else if (s_throw == "wil") {
		return Character::getModifier(Character::wisdom) + char_class.will;
	}
	else {
		return 419;
	}
}

int Character::getAttackBonus(std::string attack, CharacterClass char_class) {
	if (attack == "mel") {
		return Character::getModifier(Character::getAbilityScore("str")) + char_class.base_attack_bonus;
	}
	else if (attack == "ran") {
		return Character::getModifier(Character::getAbilityScore("dex")) + char_class.base_attack_bonus;
	}
	else {
		return 419;
	}
}

uint8_t Character::getLevel() {
	return Character::level;
}

void Character::setLevel(uint8_t val) {
	Character::level = val;
}

void Character::modXP(std::string op, int val) {
	if (op == "add") {
		Character::xp += val;
	}
	else if (op == "sub") {
		Character::xp -= val;
	}
	else {
		return;
	}
}

int Character::getSkillModifier(Skill skill) {
	return (skill.ranks + (Character::getModifier(Character::getAbilityScore(skill.ability))));
}

std::string Character::getSkillName(Skill skill) {
	return skill.name;
}

Character::Character(std::string name, std::string race, std::string character_class, int str, int dex, int con, int intel, int wis, int cha) // strength, dex, con, int, wis, cha
{
	Character::name = name;
	Character::character_class = character_class;
	Character::race = race;

	Character::strength = str;
	Character::dexterity = dex;
	Character::constitution = con;
	Character::intelligence = intel;
	Character::wisdom = wis;
	Character::charisma = cha;

	Character::money[0] = 0; // we don't want the player to start out with -8k money
	Character::money[1] = 0;
	Character::money[2] = 0;
	Character::money[3] = 0;

	Character::xp = 0;	// player also shouldn't start with -8k xp

	Character::level = 0; // we will need to know what level to load, but shouldn't be initialized to anything
}


Character::~Character()
{
}
