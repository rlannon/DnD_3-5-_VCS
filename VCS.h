#pragma once
#include "stdafx.h"
#include "Character.h"

/***********************************************************
****************		VCS.H				****************
****************	  version 1			    ****************
************************************************************

The VCS format is at the center of this program; it is what we use to save instances of players. With a VCS file, we can save and load all of a player's data without much hassle. It saves an instance of the Character class, which gives the information we need to load all other data about the player. The format is specified as follows:

	char header[7] = "v35VCSf"
	const uint8_t vcs_version = 1

	string name
	string race
	string class

	uint16_t xp
	
	uint8_t strength
	uint8_t dexterity
	uint8_t constitution
	uint8_t intelligence
	uint8_t wisdom
	uint8_t charisma

	uint8_t flat_footed
	uint8_t initiative

	uint16_t cp	-> these get saved to "int money[4]"
	uint16_t sp
	uint16_t gp
	uint16_t pp
*/

const uint8_t vcs_version = 1;

void saveToVCS(std::ostream& file, Character character);
void loadVCS(std::ostream& file, Character* character);