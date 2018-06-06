#include "Weapon.h"

Weapon::Weapon(std::string name, int id, float weight, int cost[4], std::string notes, short damage_s, short damage_m, short critical, short range, std::string type) : Item(name, id, weight, cost, notes) {
	Weapon::damage_s = damage_s;
	Weapon::damage_m = damage_m;
	Weapon::critical = critical;
	Weapon::range = range;
	Weapon::type = type;
}

Weapon::Weapon()
{
}


Weapon::~Weapon()
{
}
