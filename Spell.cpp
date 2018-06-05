#include "Spell.h"

uint8_t Spell::getLevel() {
	return spell_level;
}

std::string Spell::getValue(std::string value) {
	if (value == "name") {
		return Spell::name;
	}
	else if (value == "class" || value == "associated class") {
		return Spell::associated_class;
	}
	else if (value == "components") {
		return Spell::components;
	}
	else if (value == "cast time" || value == "casting time") {
		return Spell::casting_time;
	}
	else if (value == "range") {
		return Spell::range;
	}
	else if (value == "target") {
		return Spell::target;
	}
	else if (value == "duration") {
		return Spell::duration;
	}
	else if (value == "saving throw") {
		return Spell::saving_throw;
	}
	else if (value == "spell resistance") {
		if (Spell::spell_resistance) {
			return "Yes";
		}
		else {
			return "No";
		}
	}
	else if (value == "description") {
		return Spell::description;
	}
	else {
		return "Error: invalid input in function \"Spell::getValue(std::string value)\"!";
	}
}

//////////////////////// CONSTRUCTOR AND DESTRUCTOR ////////////////////////

Spell::Spell(std::string name, std::string associated_class, uint8_t spell_level, std::string components, std::string casting_time, std::string range, std::string target, std::string duration, std::string saving_throw, bool spell_resistance){
	Spell::name = name;
	Spell::associated_class = associated_class;
	Spell::spell_level = spell_level;
	Spell::components = components;
	Spell::casting_time = casting_time;
	Spell::range = range;
	Spell::target = target;
	Spell::duration = duration;
	Spell::saving_throw = saving_throw;
	Spell::spell_resistance = spell_resistance;
}

Spell::Spell()
{
}


Spell::~Spell()
{
}
