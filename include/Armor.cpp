#include "Armor.h"

short Armor::getValue(std::string val) {
	if (val == "ac_bonus") {
		return ac_bonus;
	}
	else if (val == "max_dex") {
		return max_dex;
	}
	else if (val == "speed_30") {
		return speed_30;
	}
	else if (val == "speed_20") {
		return speed_20;
	}
	else if (val == "armor_check_penalty" || val == "check_penalty") {
		return armor_check_penalty;
	}
}

float Armor::getSpellFailChance() {
	return spell_fail_chance;
}

void Armor::newArmor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20 ){
	Armor::name = name;
	Armor::id = id;
	Armor::weight = weight;

	for (int i = 0; i < 4; i++) {
		Armor::cost[i] = cost[i];
	}

	Armor::notes = notes;
	
	Armor::ac_bonus = ac_bonus;
	Armor::max_dex = max_dex;
	Armor::armor_check_penalty = check_penalty;
	Armor::spell_fail_chance = fail_chance;
	Armor::speed_30 = speed_30;
	Armor::speed_20 = speed_20;
}

Armor::Armor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20) : Item(name, id, weight, cost, notes) { // see weapon.h and weapon.cpp for initializer information
	Armor::ac_bonus = ac_bonus;
	Armor::max_dex = max_dex;
	Armor::armor_check_penalty = check_penalty;
	Armor::spell_fail_chance = fail_chance;
	Armor::speed_30 = speed_30;
	Armor::speed_20 = speed_20;
}

Armor::Armor()
{
}


Armor::~Armor()
{
}
