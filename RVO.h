#pragma once
#include "stdafx.h"
#include "Item.h"
#include "Weapon.h"
#include "Armor.h"

/* RVO - RKS Virtual Object Format
Overview and description of the format

This file establishes the RVO format, used to store items used in RKS. It is possible that this file format will eventually include the RVC and RVR formats, but as of version 1, it is only used to store the Item class and its child classes, Weapon and Armor.
RVO files store multiple objects in them, but all objects must be of the same type. This allows us to store weapon data in one file, armor data in another, and misc item data in another. That way, we do not need a file for every individual object. Special items may get their own objects, but that is up to the implementation author.
Since this file format uses floats as data types, we must include a "convertFloat" function to move the data to and from float to uint8_t/uint16_t. This is done by multiplying and dividing by ten as many times as the precision we need (2 decimal places). These functions are found in the FundamentalDataTypes file.

The file is laid out as follows; the first section contains the Item data, and is used for all three types:
	char header[4] = "RVOf"
	uint8_t version
	uint8_t type
		1 - Item
		2 - Weapon
		3 - Armor
	uint16_t num_items;

	For each item:

	uint16_t item_id
	string name
	
	float weight - converted to uint32_t, with 3 decimal places precision (max value over 399,999)
		note that we are using a u32 because a u16 only lets us have items with weights up to 655--any higher and it causes an underflow

	uint16_t cost[4]

If the file contains an "Item" type, we are done. If, however, the file contains a Weapon or Armor type, we continue:

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

// functions to make our lives easier / the code easier to read
void writeHeader(std::ostream& file);
void writeItemData(std::ostream& file, Item item);

bool readHeader(std::istream& file); // returns 1 if valid RVO file
void readItemData(std::istream& file, Item* item);

// save our items to RVO format; we must save from a vector
void saveToRVO(std::ostream& file, std::vector<Item> item);
void saveToRVO(std::ostream& file, std::vector<Weapon> weapon);
void saveToRVO(std::ostream& file, std::vector<Armor> armor);

// load from RVO format to vector
void loadToVector_RVO(std::istream& file, std::vector<Item>* item);
void loadToVector_RVO(std::istream& file, std::vector<Weapon>* weapon);
void loadToVector_RVO(std::istream& file, std::vector<Armor>* armor);

// load individual object from RVO
void loadItem_RVO(std::istream& file, Item* item, int item_id);
void loadItem_RVO(std::istream& file, Weapon* weapon, int item_id);
void loadItem_RVO(std::istream& file, Armor* armor, int item_id);