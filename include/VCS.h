#pragma once
#include "stdafx.h"
#include "Character.h"
#include "CharacterClass.h"
#include "Race.h"

/***********************************************************
****************		VCS.H				****************
****************	  version 1			    ****************
************************************************************

The VCS format is at the center of this program; it is what we use to save instances of players. With a VCS file, we can save and load all of a player's data without much hassle. It saves an instance of the Character class, which gives the information we need to load all other data about the player. The format is specified as follows:

	char header[7] = "v35VCSf"
	const uint8_t vcs_version = 2

	string name
	string char_race_name  -> these will both be used to load the correct file for Race and CharacterClass
	string char_class_name -> 

	uint16_t xp
	
	uint8_t strength
	uint8_t dexterity
	uint8_t constitution
	uint8_t intelligence
	uint8_t wisdom
	uint8_t charisma

	uint8_t initiative_mod

	uint16_t cp	-> these get saved to "int money[4]"
	uint16_t sp
	uint16_t gp
	uint16_t pp

After the code to write the VCS file, the VCS format saves the character inventory vectors as separate .inventory.rvo files; this allows us to more cleanly manage player data and inventories, but still save and load these inventories using VCS functions.

*/

const short vcs_version = 2;

void saveToVCS(std::ostream& file, Character character);
void loadVCS(std::istream& file, Character* character);

// When loading data to a character, use this function -- loadVCS just loads VCS data, loadCharacter loads all data (class data, etc.) into a character object
void loadCharacter(std::istream& vcs_file, Character* character, CharacterClass* char_class, Race* char_race);