#include "stdafx.h"
#include "ClassData.h"

uint8_t ClassData::getBaseAttackBonus(int n) {
	return (uint8_t)ClassData::base_attack_bonus[n];
}

uint8_t ClassData::getSavingThrow(std::string s_throw, int n) {
	if (s_throw == "for") {
		return (uint8_t)ClassData::fortitude[n];
	}
	else if (s_throw == "ref") {
		return (uint8_t)ClassData::reflex[n];
	}
	else if (s_throw == "wil") {
		return (uint8_t)ClassData::will[n];
	}
	else {
		return 49;
	}
}

uint8_t ClassData::getHitDie() {
	return (uint8_t)ClassData::hit_die;
}

uint8_t ClassData::getSkillCoefficient() {
	return (uint8_t)ClassData::skill_coefficient;
}

uint8_t ClassData::getClassSkillFlag(uint8_t n) {
	return (uint8_t)ClassData::classSkillFlag[n];
}

std::string ClassData::getName() {
	return ClassData::name;
}

ClassData::ClassData(std::string name, unsigned short bab[20], unsigned short fortitude[20], unsigned short reflex[20], unsigned short will[20], unsigned short hit_die, unsigned short skill_coefficient, bool classSkillFlag[num_skills]) {
	ClassData::name = name;

	for (int i = 0; i < 20; i++) {
		ClassData::base_attack_bonus[i] = bab[i];
		ClassData::fortitude[i] = fortitude[i];
		ClassData::reflex[i] = reflex[i];
		ClassData::will[i] = will[i];
	}

	ClassData::hit_die = hit_die;
	ClassData::skill_coefficient = skill_coefficient;

	for (int i = 0; i < num_skills; i++) {
		ClassData::classSkillFlag[i] = classSkillFlag[i];
	}
}

ClassData::ClassData() {

}

ClassData::~ClassData() {
}