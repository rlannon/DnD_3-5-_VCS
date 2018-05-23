#include "CharacterClass.h"

/****************************************************************************************************************************
*****************************************************************************************************************************

					  ****************	  FUNCTIONS TO LOAD FROM FILE TO CHARACTER CLASS	****************

*****************************************************************************************************************************
****************************************************************************************************************************/



void CharacterClass::setBaseAttackBonus(uint8_t val) {
	CharacterClass::base_attack_bonus = val;
}

void CharacterClass::setSavingThrow(std::string s_throw, uint8_t val) {
	if (s_throw == "for") {
		CharacterClass::fortitude = val;
	}
	else if (s_throw == "ref") {
		CharacterClass::reflex = val;
	}
	else if (s_throw == "wil") {
		CharacterClass::will = val;
	}
	else {
		return;
	}
}

void CharacterClass::setHitDie(uint8_t val) {
	CharacterClass::hit_die = val;
}

void CharacterClass::setSkillCoefficient(uint8_t val) {
	CharacterClass::skill_coefficient = val;
}

void CharacterClass::setName(std::string str) {
	CharacterClass::name = str;
}

// This function sets data about all class flags for a given level; it is used in our load function
void CharacterClass::setClassSkillFlag(bool skill[35]) {
	for (int i = 0; i < 35; i++) {
		CharacterClass::classSkillFlag[i] = skill[i];
	}
}



/*****************************************

		Constructor and Destructor

*****************************************/



CharacterClass::CharacterClass(std::string name, short base_attack_bonus, unsigned short fortitude, unsigned short reflex, unsigned short will, unsigned short hit_die, unsigned short skill_coefficient)
{
	CharacterClass::name = name;
	CharacterClass::base_attack_bonus = base_attack_bonus;
	CharacterClass::fortitude = fortitude;
	CharacterClass::reflex = reflex;
	CharacterClass::will = will;
	CharacterClass::hit_die = hit_die;
	CharacterClass::skill_coefficient = skill_coefficient;

	for (int i = 0; i < 35; i++) {
		CharacterClass::classSkillFlag[i] = 0;
	}
}

CharacterClass::CharacterClass() {
	CharacterClass::name = "0";
	CharacterClass::base_attack_bonus, CharacterClass::fortitude, CharacterClass::reflex, CharacterClass::will, CharacterClass::hit_die, CharacterClass::skill_coefficient = 0;
	for (int i = 0; i < 35; i++) {
		CharacterClass::classSkillFlag[i] = 0;
	}
}

CharacterClass::~CharacterClass()
{
}