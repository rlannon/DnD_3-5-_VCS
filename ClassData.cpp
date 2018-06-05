#include "stdafx.h"
#include "ClassData.h"

bool ClassData::isCaster() {
	return ClassData::is_caster;
}

uint8_t ClassData::getBaseAttackBonus(int n) {
	return (uint8_t)ClassData::base_attack_bonus[n];
}

uint8_t ClassData::getSavingThrow(std::string s_throw, int n) {
	if (s_throw == "for" || s_throw == "fortitude") {
		return (uint8_t)ClassData::fortitude[n];
	}
	else if (s_throw == "ref" || s_throw == "reflex") {
		return (uint8_t)ClassData::reflex[n];
	}
	else if (s_throw == "wil" || s_throw == "will") {
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

uint8_t ClassData::getVectorSize(std::string vector_name) {
	if (vector_name == "spell" || vector_name == "spells") {
		return (uint8_t)ClassData::class_spells.size();
	}
	else if (vector_name == "skill" || vector_name == "skills") {
		return (uint8_t)ClassData::class_skill_vector.size();
	}
}

Skill ClassData::getSkillFromVector(int i) {
	return ClassData::class_skill_vector[i];
}

uint8_t ClassData::getSpellsPerDay(int i) {
	return ClassData::spells_per_day_by_level[i];
}

uint8_t ClassData::getSpellsKnown(int i) {
	return ClassData::spells_known_by_level[i];
}

Spell ClassData::getSpellFromVector(int i) {
	return ClassData::class_spells[i];
}

void ClassData::addSpell(Spell spell) {
	ClassData::class_spells.push_back(spell);
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