#pragma once
#include "stdafx.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Spell.h"

/*

RVC - Rijksystem Virtual Class

Version 2

Version 1 of this file format did not include the spell vector data. Reading from a version 1 file will ignore the spell vector.

This library establishes RVC file format, which is to be used for storing all the RKS character class data. The header lays out the file format, and the C++ file implements it. Note this is to be used in conjunction with a CharacterClass object from this program. The file is format contains the following types, and is structured as follows:

	char header[5] = "RVCf";

	uint8_t version;

	(bool)uint8_t magic_caster

	uint8_t base_attack_bonus[20];

	uint8_t fortitude[20];
	uint8_t reflex[20];
	uint8_t will[20];

	uint8_t hit_die;

	uint8_t skill_coefficient;

	vector<Skill> class_skill_vector:
		class_skill_vector.size();
		all class_skill_vector data:
			name
			ability
			is_untrained()

	uint8_t spells_per_day[20]
	uint8_t spells_known[20]

	vector<Spell> class_spells:
		class_spells.size();
		all class_spells data

	uint32_t len;
	string name;

*/

const short rvc_version = 2;

void saveToRVC(std::ostream& file, ClassData class_obj);
void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);

void loadClassData_RVC(std::istream& file, ClassData* class_obj);

short getFileVersion(std::istream& file);