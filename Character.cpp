#include "Character.h"

std::string Character::getName() {
	return Character::name;
}

std::string Character::getRace() {
	return Character::race;
}

std::string Character::getClass() {
	return Character::char_class;
}

int Character::getMaxHitPoints(CharacterClass char_class) {
	return ((int)Character::getLevel() * (Character::getModifier(Character::getAbilityScore("con")) + char_class.hit_die));
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

int Character::calcArmorClass() {
	return 0;
}

int Character::calcFlatFooted() {
	return 0;
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

// getLevel() returns the character's level given their current xp;
uint8_t Character::getLevel() {
	int xp_req = 0;
	int lvl = 0;
	/*
	The amount of xp needed to reach the next level is adding (current_level * 1000) to your xp. Given that a formula exists, we can write an algorithm to calculate the current level based on xp. We will have to use a for() loop. The algorithm is as follows:
		1. calculate xp needed to achieve the current level for our iterator, i, storing in xp_req;
		2. check whether player's xp is greater than that experience;
			a. if the player's xp is greater than xp_req, increment i and go back to step 1;
			b. if the player's xp is less than xp_req, lvl = i-1;
			c. if the player's xp is /exactly equal/ to xp_req, lvl = i;
	*/

	for (int i = 1; i < 21; i++) {
		xp_req += i * 1000;
		if (Character::xp == xp_req) {
			lvl = i;
			break;
		}
		else if (Character::xp > xp_req) {
			continue; // go back to the top of the loop; not done checking
		}
		else if (Character::xp < xp_req) {
			lvl = i - 1;
			break;
		}
	}
	return lvl;
}

int Character::getSkillModifier(Skill skill) {
	return (skill.ranks + (Character::getModifier(Character::getAbilityScore(skill.ability))));
}

std::string Character::getSkillName(Skill skill) {
	return skill.name;
}

// This initializer would be best for starting a new character, or creating a test character
Character::Character(std::string name, std::string race, std::string char_class, int str, int dex, int con, int intel, int wis, int cha) // strength, dex, con, int, wis, cha
{
	Character::name = name;
	Character::char_class = char_class;
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
}

// This initializer should be used when loading character data from a file
Character::Character() {
	Character::name, Character::char_class, Character::race = "";
	Character::strength, Character::dexterity, Character::constitution, Character::intelligence, Character::wisdom, Character::charisma = 0;
	Character::money[0], Character::money[1], Character::money[2], Character::money[3] = 0;
	Character::xp = 0;
}


Character::~Character()
{
}
