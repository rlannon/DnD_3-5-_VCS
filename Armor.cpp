#include "Armor.h"

Armor::Armor(std::string name, int id, float weight, int cost[4], std::string notes, short ac_bonus, short max_dex, short check_penalty, float fail_chance, short speed_30, short speed_20) : Item(name, id, weight, cost, notes) {
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
