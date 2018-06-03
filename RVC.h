#pragma once
#include "stdafx.h"
#include "CharacterClass.h"
#include "ClassData.h"

/*

RVC - Rijksystem Virtual Class

This library establishes RVC file format, which is to be used for storing all the RKS character class data. The header lays out the file format, and the C++ file implements it. Note this is to be used in conjunction with a CharacterClass object from this program. The file is format contains the following types, and is structured as follows:

	char header[5] = "RVCf";

	uint8_t version;

	uint8_t base_attack_bonus;

	uint8_t fortitude;
	uint8_t reflex;
	uint8_t will;

	uint8_t hit_die;

	uint8_t classSkillFlag[35]

	uint32_t len;
	string name;

*/

const uint8_t rvc_version = 1;

void saveToRVC(std::ostream& file, ClassData class_obj);
void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);

void loadClassData_RVC(std::istream& file, ClassData* class_obj);