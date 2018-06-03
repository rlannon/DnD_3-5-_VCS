#pragma once
#include "stdafx.h"
#include "CharacterClass.h"
#include "stdafx.h"
#include "Race.h"
#include "Skill.h"
#include "CharacterClass.h"

/*

This class is a way to track all data about the player. It relies on other classes for some of its data that isn't directly related to the player, such as class and equipment data; that is stored in its appropriate class and used by Character.

*/

class Character
{
	friend void saveToVCS(std::ostream& file, Character character);
	friend void loadVCS(std::istream& file, Character* character);
protected:
	CharacterClass* char_class;
	Race* char_race;
	Skill* char_skills[num_skills];

	std::string name;
	std::string race_name;
	std::string char_class_name;

	int xp; // initialized to 0

	// abilities
	int strength;
	int dexterity;
	int constitution;
	int intelligence;
	int wisdom;
	int charisma;

	// combat
	int initiative_mod;

	// level up data
	int ranks_to_use;
	bool ability_score_increase_flag;
	bool add_feat_flag;

	// misc
	int money[4]; // money[0] = cp, money[1] = sp, money[2] = gp, money[3] = pp
public:
	std::string getName();
	std::string getRace();
	std::string getClass();

	void setCharacterRace(Race* char_race);
	void setCharacterClass(CharacterClass* char_class);

	int getMaxHitPoints();
	
	int getAbilityScore(std::string ability);
	int getModifier(int ability_score);

	int calcArmorClass();
	int calcFlatFooted();

	int getSavingThrow(std::string s_throw);
	int getAttackBonus(std::string attack);

	uint8_t getLevel();

	void modXP(std::string op, int val);

	int getSkillModifier(Skill skill);
	std::string getSkillName(Skill skill);
	bool getSkillFlagStatus(int i);

	void addSkillRank(std::string skill_name, int num_ranks);
	void increaseAbilityScore(std::string name);

	void levelUp();

	void createNewCharacter(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha);

	Character(CharacterClass* char_class, Race* char_race, Skill* char_skill_ptr, std::string name, int str, int dex, int con, int intel, int wis, int cha);
	Character();
	~Character();
};

