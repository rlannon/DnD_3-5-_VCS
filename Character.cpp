#include "Character.h"

std::string Character::getName() {
	return Character::name;
}

std::string Character::getRace() {
	return Character::race_name;
}

std::string Character::getClass() {
	return Character::char_class_name;
}

// SET CLASS AND RACE

void Character::setCharacterRace(Race* char_race) {
	Character::char_race = char_race;
}
void Character::setCharacterClass(CharacterClass* char_class) {
	Character::char_class = char_class;
}

// GET VALUES

int Character::getMaxHitPoints() {
	return (((int)Character::getLevel()+1) * (Character::getModifier(Character::getAbilityScore("con")) + Character::char_class->hit_die));
}

int Character::getModifier(int ability_score) {
	return ((ability_score - 10) / 2);
}

int Character::getAbilityScore(std::string ability) {
	if (ability == "strength" | ability == "str") {
		return (Character::strength + Character::char_race->str_bonus);
	}
	else if (ability == "constitution" | ability == "con") {
		return (Character::constitution + Character::char_race->con_bonus);
	}
	else if (ability == "dexterity" | ability == "dex") {
		return (Character::dexterity + Character::char_race->dex_bonus);
	}
	else if (ability == "intelligence" | ability == "int") {
		return (Character::intelligence + Character::char_race->int_bonus);
	}
	else if (ability == "wisdom" | ability == "wis") {
		return (Character::wisdom + Character::char_race->wis_bonus);
	}
	else if (ability == "charisma" | ability == "cha") {
		return (Character::charisma + Character::char_race->cha_bonus);
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

int Character::getSavingThrow(std::string s_throw) {
	if (s_throw == "fortitude" | s_throw == "for") {
		return Character::getModifier(Character::getAbilityScore("con") + Character::char_class->fortitude);
	}
	else if (s_throw == "reflex" | s_throw == "ref") {
		return Character::getModifier(Character::getAbilityScore("dex")) + Character::char_class->reflex;
	}
	else if (s_throw == "will" | s_throw == "wil") {
		return Character::getModifier(Character::getAbilityScore("wis")) + Character::char_class->will;
	}
	else {
		return 419;
	}
}

int Character::getAttackBonus(std::string attack) {
	if (attack == "melee" | attack == "mel") {
		return Character::getModifier(Character::getAbilityScore("str")) + Character::char_class->base_attack_bonus;
	}
	else if (attack == "ranged" | attack == "ran") {
		return Character::getModifier(Character::getAbilityScore("dex")) + Character::char_class->base_attack_bonus;
	}
	else {
		return 419;
	}
}

void Character::modXP(std::string op, int val) {
	if (op == "add") {
		Character::xp += val;
	}
	else if (op == "sub" | op == "subtract") {
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

bool Character::getSkillFlagStatus(int i) {
	return Character::char_class->classSkillFlag[i];
}

void Character::addSkillRank(std::string skill_name, int num_ranks) {
	for (int i = 0; i < num_skills; i++) {
		if (Character::char_skills[i]->name == skill_name) {
			if ((Character::char_skills[i]->ranks + num_ranks) <= Character::char_skills[i]->getMaxRanks(Character::getLevel())) {
				Character::char_skills[i]->ranks += num_ranks;
			}
		}
	}
}

////////////////////////////////////////////////////////////////
//////////////			  LEVEL UP			  //////////////////
////////////////////////////////////////////////////////////////

void Character::levelUp() {
	ranks_to_use += (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence));
}

// use this void to set new class values without initializing a new class
void Character::createNewCharacter(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha) {
	Character::char_class = char_class;
	Character::char_race = char_race;

	for (int i = 0; i < num_skills; i++) {
		char_skills[i] = char_skill_ptr + i;
		char_skills[i]->is_class_skill = Character::char_class->classSkillFlag[i];
	}

	Character::name = name;
	Character::char_class_name = char_class->name;
	Character::race_name = char_race->name;

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

	Character::ranks_to_use = (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence)) * 4; // level 1 ranks

	Character::xp = 0;	// player also shouldn't start with -8k xp
}

// This initializer would be best for starting a new character, or creating a test character
Character::Character(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha) // strength, dex, con, int, wis, cha
{
	Character::char_class = char_class;
	Character::char_race = char_race;

	for (int i = 0; i < num_skills; i++) {
		char_skills[i] = char_skill_ptr + i;
		char_skills[i]->is_class_skill = Character::char_class->classSkillFlag[i];
	}

	Character::name = name;
	Character::char_class_name = char_class->name;
	Character::race_name = char_race->name;

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

	Character::ranks_to_use = (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence)) * 4; // level 1 ranks

	Character::xp = 0;	// player also shouldn't start with -8k xp
}

// This initializer should be used when loading character data from a file
Character::Character() {
	Character::name, Character::char_class_name, Character::race_name = "";
	Character::strength, Character::dexterity, Character::constitution, Character::intelligence, Character::wisdom, Character::charisma = 0;
	Character::money[0], Character::money[1], Character::money[2], Character::money[3] = 0;
	Character::xp = 0;
	Character::ranks_to_use = 0;
}


Character::~Character()
{
}
