#include "stdafx.h"
#include "RVC.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "Spell.h"
#include "FundamentalDataTypes.h"

// Construct a file with the FundamentalDataTypes functions given a CharacterClass object

void saveToRVC(std::ostream& file, ClassData class_obj) {
	// write our header data
	char * header = "RVCf";
	file.write(header, 4);

	writeU8(file, rvc_version);

	writeU8(file, class_obj.isCaster());

	// now we write our data to file in the order as stated in RCC.h

	for (int i = 0; i < 20; i++) {
		writeU8(file, class_obj.getBaseAttackBonus(i));
	}
	for (int i = 0; i < 20; i++) {
		writeU8(file, class_obj.getSavingThrow("for", i));
	}
	for (int i = 0; i < 20; i++) {
		writeU8(file, class_obj.getSavingThrow("ref", i));
	}
	for (int i = 0; i < 20; i++) {
		writeU8(file, class_obj.getSavingThrow("wil", i));
	}

	// next, we write in our constants
	writeU8(file, class_obj.getHitDie());
	writeU8(file, class_obj.getSkillCoefficient());
	
	/***************************************************************
	****************************************************************
	****************			SKILL VECTOR			************
	****************************************************************
	***************************************************************/

	// write in the size of our skill vector -- how many class skills do we have?
	writeU8(file, class_obj.getVectorSize("skills"));

	// then, write all data from skills vector using a for loop
	/*for (int i = 0; i < class_obj.getVectorSize("skills"); i++) {
		writeString(file, class_obj.getSkillFromVector(i).getSkillName());
		writeString(file, class_obj.getSkillFromVector(i).getSkillAbility());
		writeU8(file, class_obj.getSkillFromVector(i).isUntrained());
	}*/
	// use a vector iterator instead
	for (std::vector<Skill>::iterator it = class_obj.class_skill_vector.begin(); it != class_obj.class_skill_vector.end(); it++) {
		writeString(file, it->getSkillName());
		writeString(file, it->getSkillAbility());
		writeU8(file, (uint8_t)it->isUntrained()); // cast bool to uint8_t
	}

	/***************************************************************
	****************************************************************
	****************			MAGIC/CASTING			************
	****************************************************************
	***************************************************************/
	
	// only do the following if our class is a casting class
	if (class_obj.isCaster()) {
		// write in our spells per day and spells known by level

		for (int i = 0; i < 20; i++) {
			writeU8(file, class_obj.getSpellsPerDay(i));
		}

		for (int i = 0; i < 20; i++) {
			writeU8(file, class_obj.getSpellsKnown(i));
		}

		// write data from spell vector

		// first, we must write in the size of our vector so we can read properly
		writeU8(file, class_obj.getVectorSize("spells"));

		// then, write all data from vector into file using a for loop
		/*
		for (int i = 0; i < class_obj.getVectorSize("spells"); i++) {
			// write spell level and whether it is subject to spell resistance
			writeU8(file, class_obj.getSpellFromVector(i).getLevel());
			writeU8(file, class_obj.getSpellFromVector(i).spellResistance());

			// write all other values
			writeString(file, class_obj.getSpellFromVector(i).getValue("name"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("associated class"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("components"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("casting time"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("range"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("target"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("duration"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("saving throw"));
			writeString(file, class_obj.getSpellFromVector(i).getValue("description"));
		}*/
		// use vector iterator instead
		for (std::vector<Spell>::iterator it = class_obj.class_spells.begin(); it != class_obj.class_spells.end(); it++) {
			// write spell level and whether it is subject to spell resistance
			writeU8(file, it->getLevel());
			writeU8(file, it->spellResistance());

			// write all other values
			writeString(file, it->getValue("name"));
			writeString(file, it->getValue("associated class"));
			writeString(file, it->getValue("components"));
			writeString(file, it->getValue("casting time"));
			writeString(file, it->getValue("range"));
			writeString(file, it->getValue("target"));
			writeString(file, it->getValue("duration"));
			writeString(file, it->getValue("saving throw"));
			writeString(file, it->getValue("description"));
		}
	} // end of "if isCaster()"

	// finally, write the class name to the file
	writeString(file, class_obj.getName());
}

void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	file.read(buffer, 4);

	// first, check our header data to make sure it is the correct file format. If so, continue on
	if (header[0, 1, 2, 3] == *"R", "V", "C", "f") {

		// get the version from the file
		vers = readU8(file);

		/*

		BRIEF EXPLANATION OF THE FOLLOWING CODE:

		The procedure is pretty simple -- use seekg() to move ahead to the correct byte for our bab/for/ref/wil data, read the value, move ahead the rest of the way to the start of the next variable we want to read. So, we move ahead with seekg(+level) from the current position -- if level == 0, then we don't move; if level == 5, we move ahead five.
		Next, we set the bonus.
		Finally, we take 20, which is the most we can skip for a given variable (20 would skip over all the members, as there are twenty of them), minus the length we have already moved, which is our character level, -1 for the block we read. Therefore, we get (20 - 1 - level), or (19-level) as is in the code.


		*/

		if (vers == 2) {
			int vector_size;
			Spell temp_spell;
			Skill temp_skill;

			bool is_caster = readU8(file);

			class_obj->is_caster = is_caster;

			// if we have a version 2 file, read the file this way
			file.seekg(+level, std::ios::cur);	// seek to current level bab data
			class_obj->setBaseAttackBonus(readU8(file));
			file.seekg(+(19 - level), std::ios::cur); // seek across the remaining bytes for bab data

													  // do the same for for, ref, and wil
			file.seekg(+level, std::ios::cur);
			class_obj->setSavingThrow("for", readU8(file));
			file.seekg(+(19 - level), std::ios::cur);

			file.seekg(+level, std::ios::cur);
			class_obj->setSavingThrow("ref", readU8(file));
			file.seekg(+(19 - level), std::ios::cur);

			file.seekg(+level, std::ios::cur);
			class_obj->setSavingThrow("wil", readU8(file));
			file.seekg(+(19 - level), std::ios::cur);

			// read hd
			class_obj->setHitDie(readU8(file));

			// read skill coefficient
			class_obj->setSkillCoefficient(readU8(file));

			// read class skills into vector
			
			// get size of vector/number of elements
			vector_size = (int)readU8(file);

			// clear the vector
			class_obj->class_skill_vector.clear();

			// read data into vector
			for (int i = 0; i < vector_size; i++) {
				temp_skill.name = readString(file);
				temp_skill.ability = readString(file);
				temp_skill.is_class_skill = (bool)readU8(file);

				// push into vector
				class_obj->class_skill_vector.push_back(temp_skill);
			}

			// only read in if we are a casting class
			if (is_caster) {
				// first, get our spells per day and spells known
				file.seekg(+level, std::ios::cur);
				class_obj->spells_per_day = (short)readU8(file);
				file.seekg(+(19 - level), std::ios::cur);

				file.seekg(+level, std::ios::cur);
				class_obj->spells_known = (short)readU8(file);
				file.seekg(+(19 - level), std::ios::cur);

				// next, get the size
				vector_size = (int)readU8(file);

				// then, clear the vector to make sure no leftover data makes its way in there
				class_obj->class_spells.clear();

				// then, read data into our vector - note vector_size is the value we saved
				for (int i = 0; i < vector_size; i++) {
					// load file data into a temp spell object
					temp_spell.spell_level = readU8(file);
					temp_spell.spell_resistance = (bool)readU8(file);
					temp_spell.name = readString(file);
					temp_spell.associated_class = readString(file);
					temp_spell.components = readString(file);
					temp_spell.casting_time = readString(file);
					temp_spell.range = readString(file);
					temp_spell.target = readString(file);
					temp_spell.duration = readString(file);
					temp_spell.saving_throw = readString(file);
					temp_spell.description = readString(file);

					// push the spell onto the end of the vector
					class_obj->class_spells.push_back(temp_spell);
				}
			}

			// read name
			class_obj->setName(readString(file));
		}
	}
	else { // incorrect file format
		return;
	}
}

void loadClassData(std::istream& file, ClassData* class_obj) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	file.read(buffer, 4);

	if (header[0, 1, 2, 3] == *"R", "V", "C", "f") {
		vers = readU8(file);

		if (vers == 2) {
			Skill temp_skill;
			int vector_size;

			// version 2 rvc file
			// check for caster status
			bool is_caster = (bool)readU8(file);
			class_obj->is_caster = is_caster;

			// get base attack
			for (int i = 0; i < 20; i++) {
				class_obj->base_attack_bonus[i] = readU8(file);
			}

			// for, ref, will
			for (int i = 0; i < 20; i++) {
				class_obj->fortitude[i] = readU8(file);
			}
			for (int i = 0; i < 20; i++) {
				class_obj->reflex[i] = readU8(file);
			}
			for (int i = 0; i < 20; i++) {
				class_obj->will[i] = readU8(file);
			}

			// hd
			class_obj->hit_die = readU8(file);
			// skill coefficient
			class_obj->skill_coefficient = readU8(file);
		
			// get vector size (num skills saved) and clear the vector
			vector_size = readU8(file);
			class_obj->class_skill_vector.clear();

			for (int i = 0; i < vector_size; i++) {
				// read from file, storing data in a temp class instance
				temp_skill.name = readString(file);
				temp_skill.ability = readString(file);
				temp_skill.untrained = (bool)readU8(file);

				// push class instance to end of vector
				class_obj->class_skill_vector.push_back(temp_skill);
			}

			if (is_caster) {
				Spell temp;
				
				for (int i = 0; i < 20; i++) {
					class_obj->spells_per_day_by_level[i] = readU8(file);
				}
				for (int i = 0; i < 20; i++) {
					class_obj->spells_known_by_level[i] = readU8(file);
				}
				vector_size = readU8(file);

				class_obj->class_spells.clear();

				for (int i = 0; i < vector_size; i++) {
					temp.spell_level = readU8(file);
					temp.spell_resistance = (bool)readU8(file);
					temp.name = readString(file);
					temp.associated_class = readString(file);
					temp.components = readString(file);
					temp.casting_time = readString(file);
					temp.range = readString(file);
					temp.target = readString(file);
					temp.duration = readString(file);
					temp.saving_throw = readString(file);
					temp.description = readString(file);

					// push the spell onto the end of the vector
					class_obj->class_spells.push_back(temp);
				}
			}

			// name
			class_obj->name = readString(file);
		}
	}
	else { // incorrect file type
		return;
	}
}

short getFileVersion(std::istream& file) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	file.seekg(4, std::ios::beg);
	vers = (short)readU8(file);

	return vers;
}