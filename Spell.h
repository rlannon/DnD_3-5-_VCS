#pragma once
#include "stdafx.h"
#include "Skill.h"

/*
	Note:

	Maybe "spells" shouldn't be stored in the RVC file...and instead in the class's respective .spells file, and loaded into characterclass from the .spells file rather than from the .rvc file. The format could be used alongside RVC and so the RVC functions would load a .spells file
	Or, just keep them with the classfile and use .spells files as a utility? For example, load the vector with the data from the .spells file and then save that vector to the .rvc file -- makes class creation and modification much easier...
	The benefit of separating the two is that it keeps them separate but linked, like they are in the book--this makes it easier to modify spells because they are linked to the class, not part of it. The downside is that it makes things a little more messy and requires shifting code around quite a bit.... The quesiton is, would there be significant benefit to doing this, even ignoring the work required to do it? If so, do it--but if not, leave it as is.
	Perhaps the way to answer is to create the format for utility, see if it is useful, and then /integrate/ it with RVC.

*/

class Spell
{
	std::string name;
	std::string associated_class;
	
	short spell_level;

	std::string components;
	std::string casting_time;
	std::string range;
	std::string target;
	std::string duration;
	std::string saving_throw;

	bool spell_resistance;
	
	std::string description;

	friend class CharacterClass;
	friend class ClassData;
	friend void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level);
	friend void loadClassData_RVC(std::istream& file, ClassData* class_obj);
	friend void modClass(Skill skill_structure[num_skills]);
public:
	short getLevel();
	bool spellResistance();
	std::string getValue(std::string value);

	void setValue(std::string name, std::string new_value);

	Spell(std::string name, std::string associated_class, uint8_t spell_level, std::string components, std::string casting_time, std::string range, std::string target, std::string duration, std::string saving_throw, bool spell_resistance);
	Spell();
	~Spell();
};

