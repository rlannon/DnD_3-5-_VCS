#include "Character.h"

std::string Character::getName() {
	return Character::name;
}

std::string Character::getRace() {
	return Character::race_name;
}

std::string Character::getClass() {
	return Character::char_class_name;
}

// SET CLASS AND RACE

void Character::setCharacterRace(Race* char_race) {
	Character::char_race = char_race;
}
void Character::setCharacterClass(CharacterClass* char_class) {
	Character::char_class = char_class;
}

// ABILITIES

int Character::getAbilityScore(std::string ability) {
	if (ability == "strength" || ability == "str") {
		return (Character::strength + Character::char_race->str_bonus);
	}
	else if (ability == "constitution" || ability == "con") {
		return (Character::constitution + Character::char_race->con_bonus);
	}
	else if (ability == "dexterity" || ability == "dex") {
		return (Character::dexterity + Character::char_race->dex_bonus);
	}
	else if (ability == "intelligence" || ability == "int") {
		return (Character::intelligence + Character::char_race->int_bonus);
	}
	else if (ability == "wisdom" || ability == "wis") {
		return (Character::wisdom + Character::char_race->wis_bonus);
	}
	else if (ability == "charisma" || ability == "cha") {
		return (Character::charisma + Character::char_race->cha_bonus);
	}
 	else {
		return 119;
	}
}

int Character::getModifier(int ability_score) {
	return ((ability_score - 10) / 2);
}

void Character::increaseAbilityScore(std::string name) {
	if (Character::ability_score_increase_flag) {
		if (name == "strength" || name == "str") {
			Character::strength++;
			Character::ability_score_increase_flag = false;
		}
		else if (name == "dexterity" || name == "dex") {
			Character::dexterity++;
			Character::ability_score_increase_flag = false;
		}
		else if (name == "constitution" || name == "con") {
			Character::constitution++;
			Character::ability_score_increase_flag = false;
		}
		else if (name == "intelligence" || name == "int") {
			Character::intelligence++;
			Character::ability_score_increase_flag = false;
		}
		else if (name == "wisdom" || name == "wis") {
			Character::wisdom++;
			Character::ability_score_increase_flag = false;
		}
		else if (name == "charisma" || name == "cha") {
			Character::charisma++;
			Character::ability_score_increase_flag = false;
		}
	}
}

// COMBAT

int Character::getMaxHitPoints() {
	return (((int)Character::getLevel() + 1) * (Character::getModifier(Character::getAbilityScore("con")) + Character::char_class->hit_die));
}

int Character::calcArmorClass() {
	return 0;
}

int Character::calcFlatFooted() {
	return 0;
}

int Character::getAttackBonus(std::string attack) {
	if (attack == "melee" || attack == "mel") {
		return Character::getModifier(Character::getAbilityScore("str")) + Character::char_class->base_attack_bonus;
	}
	else if (attack == "ranged" || attack == "ran") {
		return Character::getModifier(Character::getAbilityScore("dex")) + Character::char_class->base_attack_bonus;
	}
	else {
		return 419;
	}
}

// MAGIC

Spell Character::getSpellFromClass(std::string spell_name) {
	Spell *p = Character::char_class->class_spells.data();
	for (int i = 0; i < Character::char_class->class_spells.size(); i++) {
		if (Character::char_class->class_spells[i].getValue("name") == spell_name) {
			return Character::char_class->class_spells[i];
		}
		else {
			continue;
		}
	}
}

Spell Character::getKnownSpells(int n) {
	if (Character::char_spells.size() > 0 && n <= Character::char_spells.size() && n >= 0) {
		return Character::char_spells[n]; // should only return if we have elements in the vector, aren't past the end, and n is not negative
	}
}

void Character::addSpell(Spell spell) {
	bool char_knows_spell = false;
	for (int i = 0; i < Character::char_spells.size(); i++) {
		if (spell.getValue("name") == Character::char_spells[i].getValue("name")) {
			bool char_knows_spell = true; // set this to true if the spell is in the vector already
		}
	}
	if (!char_knows_spell) {
		Character::char_spells.push_back(spell); // if our bool is false, then add the spell to the vector
	}
	else { // if character already knows the spell -- we don't want duplicates in the vector
		return;
	}
}

// SAVING THROWS

int Character::getSavingThrow(std::string s_throw) {
	if (s_throw == "fortitude" || s_throw == "for") {
		return Character::getModifier(Character::getAbilityScore("con") + Character::char_class->fortitude);
	}
	else if (s_throw == "reflex" || s_throw == "ref") {
		return Character::getModifier(Character::getAbilityScore("dex")) + Character::char_class->reflex;
	}
	else if (s_throw == "will" || s_throw == "wil") {
		return Character::getModifier(Character::getAbilityScore("wis")) + Character::char_class->will;
	}
	else {
		return 419;
	}
}

// LEVEL FUNCTIONS

// getLevel() returns the character's level given their current xp;
uint8_t Character::getLevel() {
	int xp_req = 0;
	int lvl = 0;
	/*
	The amount of xp needed to reach the next level is adding (current_level * 1000) to your xp. Given that a formula exists, we can write an algorithm to calculate the current level based on xp. We will have to use a for() loop. The algorithm is as follows:
	1. calculate xp needed to achieve the current level for our iterator, i, storing in xp_req;
	2. check whether player's xp is greater than that experience;
	a. if the player's xp is greater than xp_req, increment i and go back to step 1;
	b. if the player's xp is less than xp_req, lvl = i-1;
	c. if the player's xp is /exactly equal/ to xp_req, lvl = i;
	*/

	for (int i = 1; i < 21; i++) {
		xp_req += i * 1000;
		if (Character::xp == xp_req) {
			lvl = i;
			break; // once this happens, break from the 'for' loop
		}
		else if (Character::xp > xp_req) {
			continue; // go back to the top of the loop; not done checking
		}
		else if (Character::xp < xp_req) {
			lvl = i - 1;
			break; // once this happens, break from the 'for' loop -- but always check the above two first
		}
	}
	return lvl;
}

void Character::modXP(std::string op, int val) {
	if (op == "add") {
		Character::xp += val;
	}
	else if (op == "sub" || op == "subtract") {
		Character::xp -= val;
	}
	else {
		return;
	}
}

void Character::levelUp() {
	// add skill ranks
	ranks_to_use += (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence));
	// check to see if we need to add an ability score increase
	if (Character::getLevel() % 4 == 0) {
		Character::ability_score_increase_flag = true;
	}
	if (Character::getLevel() % 3 == 0) {
		Character::add_feat_flag = true;
	}
}

// SKILL FUNCTIONS

int Character::getSkillModifier(Skill skill) {
	return (skill.ranks + (Character::getModifier(Character::getAbilityScore(skill.ability))));
}

std::string Character::getSkillName(Skill skill) {
	return skill.name;
}

void Character::addSkillRank(std::string skill_name, int num_ranks) {

}

Skill Character::getSkill(int i) {
	if (i >= 0 && i <= Character::char_skills_vector.size()) {
		return Character::char_skills_vector[i];
	}
}

int Character::getNumSkills() {
	return Character::char_skills_vector.size();
}

void Character::addItem(Item item)
{
	Character::char_items.push_back(item);
}

void Character::addItem(Weapon weapon)
{
	Character::char_wpns.push_back(weapon);
}

void Character::addItem(Armor armor)
{
	Character::char_armor.push_back(armor);
}

// use this void to set new class values without initializing a new class
void Character::createNewCharacter(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha) {
	Character::char_class = char_class;
	Character::char_race = char_race;

	Character::name = name;
	Character::char_class_name = char_class->name;
	Character::race_name = char_race->name;

	Character::strength = str;
	Character::dexterity = dex;
	Character::constitution = con;
	Character::intelligence = intel;
	Character::wisdom = wis;
	Character::charisma = cha;

	Character::money[0] = 0; // we don't want the player to start out with -8k money
	Character::money[1] = 0;
	Character::money[2] = 0;
	Character::money[3] = 0;

	Character::ranks_to_use = (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence)) * 4; // level 1 ranks
	Character::ability_score_increase_flag = false;
	Character::add_feat_flag = false;

	// clear inventory
	Character::char_items.clear();
	Character::char_wpns.clear();
	Character::char_armor.clear();

	Character::xp = 0;	// player also shouldn't start with -8k xp

	Character::char_skills_vector.clear();

	// we will create an iterator to count through our vectors, and use our for loop to count through the master skill list
	std::vector<Skill>::iterator it = Character::char_class->class_skill_vector.begin();
	for (int i = 0; i < num_skills; i++) {
		// if the iterator has not reached the end of the vector
		if (it != Character::char_class->class_skill_vector.end()) {
			// if the next skill in our iterator is in our class vector, add the skill from the master list to the character vector
			if ((char_skill_ptr + i)->name == it->name) {
				Character::char_skills_vector.push_back(*(char_skill_ptr + i));
				it++;
			}
			// if it is not, but it is untrained, add it to the character vector
			else if (((char_skill_ptr + i)->name != it->name) && ((char_skill_ptr + i)->isUntrained())) {
				Character::char_skills_vector.push_back(*(char_skill_ptr + i));
			}
		}
		// if we have reached the end of the vector, but not the end of the master skill list, check to see if the rest are untrained
		else {
			if ((char_skill_ptr + i)->isUntrained()) {
				Character::char_skills_vector.push_back(*(char_skill_ptr + i));
			}
		}
	}
}

// This initializer would be best for starting a new character, or creating a test character
Character::Character(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha) // strength, dex, con, int, wis, cha
{
	Character::char_class = char_class;
	Character::char_race = char_race;

	Character::name = name;
	Character::char_class_name = char_class->name;
	Character::race_name = char_race->name;

	Character::strength = str;
	Character::dexterity = dex;
	Character::constitution = con;
	Character::intelligence = intel;
	Character::wisdom = wis;
	Character::charisma = cha;

	Character::money[0] = 0; // we don't want the player to start out with -8k money
	Character::money[1] = 0;
	Character::money[2] = 0;
	Character::money[3] = 0;

	Character::ranks_to_use = (Character::char_class->skill_coefficient + Character::getModifier(Character::intelligence)) * 4; // level 1 ranks
	Character::ability_score_increase_flag = false;
	Character::add_feat_flag = false;

	Character::xp = 0;	// player also shouldn't start with -8k xp
}

// This initializer should be used when loading character data from a file
Character::Character() {
	Character::name, Character::char_class_name, Character::race_name = "";
	Character::strength, Character::dexterity, Character::constitution, Character::intelligence, Character::wisdom, Character::charisma = 0;
	Character::money[0], Character::money[1], Character::money[2], Character::money[3] = 0;
	Character::xp = 0;
	Character::ranks_to_use = 0;
	Character::ability_score_increase_flag = false;
	Character::add_feat_flag = false;
}


Character::~Character()
{
}
