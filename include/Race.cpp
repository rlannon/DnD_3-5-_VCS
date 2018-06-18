#include "Race.h"



Race::Race(std::string name, int str_bonus, int dex_bonus, int con_bonus, int int_bonus, int wis_bonus, int cha_bonus, std::string lang)
{
	Race::name = name;
	Race::str_bonus = str_bonus;
	Race::dex_bonus = dex_bonus;
	Race::con_bonus = con_bonus;
	Race::int_bonus = int_bonus;
	Race::wis_bonus = wis_bonus;
	Race::cha_bonus = cha_bonus;

	Race::known_languages = lang;
}

Race::Race() {
	Race::name, Race::known_languages = "";
	Race::str_bonus, Race::dex_bonus, Race::con_bonus, Race::int_bonus, Race::wis_bonus, Race::cha_bonus = 0;
}

Race::~Race()
{
}
