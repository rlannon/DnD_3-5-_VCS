#pragma once
#include "stdafx.h"
#include "Race.h"

/*

RVR - Rijksystem Virtual Race

This file establishes the RVR file format, used for all of our race data. It corresponds directly to the Race class, in Race.h/cpp. It is formatted as follows:

	char header[4] = "RVRf"
	uint8_t version

	string name;

	uint8_t str_bonus;	note these are all casted
	uint8_t dex_bonus;
	uint8_t con_bonus;
	uint8_t int_bonus;
	uint8_t wis_bonus;
	uint8_t cha_bonus;

	string known_languages;

Refer to RVC, VCS, and SkillsFormat for questions regarding the code in this file

*/

const uint8_t rvr_version = 1;

void saveToRVR(std::ostream& file, Race race);
void loadRVR(std::istream& file, Race* race, std::string* err);