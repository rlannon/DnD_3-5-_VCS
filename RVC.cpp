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
	
	// write in our class skill flags
	for (int i = 0; i < num_skills; i++) {
		writeU8(file, class_obj.getClassSkillFlag(i));
	}
	
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
		writeU8(file, class_obj.getVectorSize());

		// then, write all data from vector into file using a for loop
		for (int i = 0; i < class_obj.getVectorSize(); i++) {
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
		}
	} // end of "if isCaster()"

	// finally, write the class name to the file
	writeString(file, class_obj.getName());
}

void loadRVC(std::istream& file, CharacterClass* class_obj, uint8_t level) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	bool flagBuffer[num_skills];

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

		if (vers == 1) {
			// if we are reading a version 1 file, use the following code

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

			// read class skill flags
			//This procedure is pretty simple; we get the U8 value from the file, cast it to bool, and store the values in our flagBuffer array. We then copy our flagBuffer array, containing the class skill flags, and copy it to our character class instance.
			for (int i = 0; i < num_skills; i++) {
				flagBuffer[i] = (bool*)readU8(file);
			}
			class_obj->setClassSkillFlag(flagBuffer);

			// read name
			class_obj->setName(readString(file));
		}
		else if (vers == 2) {
			int vector_size;
			Spell temp;

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

			// read class skill flags
			//This procedure is pretty simple; we get the U8 value from the file, cast it to bool, and store the values in our flagBuffer array. We then copy our flagBuffer array, containing the class skill flags, and copy it to our character class instance.
			for (int i = 0; i < num_skills; i++) {
				flagBuffer[i] = (bool*)readU8(file);
			}
			class_obj->setClassSkillFlag(flagBuffer);

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

			// read name
			class_obj->setName(readString(file));
		}
	}
	else { // incorrect file format
		return;
	}
}

void loadClassData_RVC(std::istream& file, ClassData* class_obj) {
	char header[4];
	char * buffer = &header[0];
	short vers = 0;

	file.read(buffer, 4);

	if (header[0, 1, 2, 3] == *"R", "V", "C", "f") {
		vers = readU8(file);

		if (vers == 1) {
			// version 1 rvc file

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
			// skill flags
			for (int i = 0; i < num_skills; i++) {
				class_obj->classSkillFlag[i] = (bool)readU8(file);
			}
			// name
			class_obj->name = readString(file);
		}
		else if (vers == 2) {
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
			// skill flags
			for (int i = 0; i < num_skills; i++) {
				class_obj->classSkillFlag[i] = (bool)readU8(file);
			}

			if (is_caster) {
				Spell temp;
				for (int i = 0; i < 20; i++) {
					class_obj->spells_per_day_by_level[i] = readU8(file);
				}
				for (int i = 0; i < 20; i++) {
					class_obj->spells_known_by_level[i] = readU8(file);
				}
				int vector_size = readU8(file);

				std::cout << vector_size << std::endl;

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