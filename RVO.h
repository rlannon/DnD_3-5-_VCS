#pragma once
#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

/* RVO - RKS Virtual Object Format
Overview and description of the format

This file establishes the RVO format, used to store items in RKS. It is a "Virtual Object File". It is similar to RVC and RVR -- they are all Object files -- but this specifically stores real-world items and objects that are usable by the player.
RVO files can store multiple objects in them; they are tracked using "num_objects" at the head of the file and "object_type" at the head of each object. This allows us to store weapon data in one file, armor data in another, and misc item data in another. This also allows player inventory to be tracked in That way, we do not need a file for every individual object. Special items may get their own objects, but that is up to the implementation author.
Since this file format uses floats as data types, we must include a "convertFloat" function to move the data to and from float to uint8_t/uint16_t. This is done by multiplying and dividing by ten as many times as the precision we need (2 decimal places). These functions are found in the FundamentalDataTypes file.

The file is laid out as follows; the first section contains the Item data, and is used for all three types:
	char header[4] = "RVOf"
	uint8_t version
	uint8_t type
		1 - Item only
		2 - Weapon only
		3 - Armor only
		4 - multi
	uint16_t num_objects;

	For each item:

	uint8_t object_type (Item = 1, Weapon = 2, Armor = 3)
	uint16_t item_id
	string name
	
	float weight - converted to uint32_t, with 3 decimal places precision (max float value over 399,999; u32 stores numbers over 4 billion)
		note that we are using a u32 because a u16 only lets us have items with weights up to 655--any higher and it causes an underflow

	uint16_t cost[4]

If the object is an "Item" type, we are done. If, however, it is a Weapon or Armor type, we continue:

If "Weapon" (type = 2)
	uint8_t dmg_s
	uint8_t dmg_m
	uint8_t critical
	uint8_t range

	string type

If "Armor" (type = 3)
	uint8_t ac_bonus
	uint8_t max_dex
	uint8_t armor_check_penalty

	float spell_fail_chance (converted to u8)

	uint8_t speed_30
	uint8_t speed_20

*/

// constants for the format
const short rvo_version = 1;

const short obj_is_item = 1;
const short obj_is_weapon = 2;
const short obj_is_armor = 3;

const short multiple_obj_types = 4;

const short obj_is_charclass = 5;
const short obj_is_race = 6;

// functions to make our lives easier / the code easier to read
void writeHeader(std::ostream& file);
void writeItemData(std::ostream& file, Item item);

bool readHeader(std::istream& file); // returns 1 if valid RVO file
short getObjTypes(std::istream& file); // tells us whether it is item-only, weapon-only, object-only, or multi-type file

void readItemData(std::istream& file, Item* item);


// save our items to RVO format; we must save from a vector
void saveToRVO(std::ostream& file, std::vector<Item> item);
void saveToRVO(std::ostream& file, std::vector<Weapon> weapon);
void saveToRVO(std::ostream& file, std::vector<Armor> armor);
// for inventory
void saveToRVO(std::ostream& file, std::vector<Item> item, std::vector<Weapon> wpn, std::vector<Armor> armor);

// load from RVO format to vector
void loadToVector_RVO(std::istream& file, std::vector<Item>* item);
void loadToVector_RVO(std::istream& file, std::vector<Weapon>* weapon);
void loadToVector_RVO(std::istream& file, std::vector<Armor>* armor);
// for inventory
void loadToVector_RVO(std::istream& file, std::vector<Item>* item, std::vector<Weapon>* weapon, std::vector<Armor>* armor);

// load individual object from RVO
void loadItem_RVO(std::istream& file, Item* item, int item_id);
void loadItem_RVO(std::istream& file, Weapon* weapon, int item_id);
void loadItem_RVO(std::istream& file, Armor* armor, int item_id);