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
	..."name" string data...

*/

const uint16_t version = 1;

// Our read/write functions
// Note uint8_t can be stored "as is", but we must break down 16 into 2 chunks

uint8_t readU8(std::istream& file);
void writeU8(std::ostream& file, uint8_t val);

uint16_t readU16(std::istream& file);
void writeU16(std::ostream& file, uint16_t val);

// Must write the length of the string to the file, then the string data so we know how long our string actually is

std::string readString(std::istream& file);
void writeString(std::ostream& file, std::string str);

void saveClassStructure(std::ostream& file, ClassData class_obj);
void loadClassData(std::istream& file, CharacterClass* class_obj, uint8_t level, std::string* err);