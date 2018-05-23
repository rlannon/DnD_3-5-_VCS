#pragma once
#include "stdafx.h"
#include "Skill.h"

/***********************************************************

****************		SKILLSFORMAT.H		****************
						  version 1

This file lays out the data for our SKILLS files.
These .skills files will contain the array containing all information about class skills. It is formatted as follows:

	char header[7] = "SKILLSf"
	uint8_t version

	For each skill:
		string name
		string ability

		bool is_general
***********************************************************/

const uint8_t skill_version = 1;

void saveSkillStructure(std::ostream& file, Skill skill_structure[35]); // save "skill" to file
void loadSkillStructure(std::istream& file, Skill * skill_ptr, std::string* err); // load from file into "skill"