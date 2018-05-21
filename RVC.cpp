#include "stdafx.h"
#include "RVC.h"
#include "CharacterClass.h"
#include "ClassData.h"
#include "FundamentalDataTypes.h"

// Construct a file with the FundamentalDataTypes functions given a CharacterClass object

void saveClassStructure(std::ostream& file, ClassData class_obj) {
	// write our header data
	char * header = "RVCf";
	file.write(header, 4);
	writeU8(file, rvc_version);

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
	for (int i = 0; i < 35; i++) {
		writeU8(file, class_obj.getClassSkillFlag(i));
	}

	// finally, write the class name to the file
	writeString(file, class_obj.getName());
}

void loadClassData(std::istream& file, CharacterClass* class_obj, uint8_t level, std::string* err) {
	char header[4];
	char * buffer = &header[0];
	uint8_t vers;

	bool flagBuffer[35];

	file.read(buffer, 4);

	// first, check our header data to make sure it is the correct file format. If so, continue on
	if (header[0, 1, 2, 3] == *"R", "V", "C", "f") {

		// get the version from the file
		vers = readU8(file);

		// write code to control for version here, if desired

		/*

		BRIEF EXPLANATION OF THE FOLLOWING CODE:

		The procedure is pretty simple -- use seekg() to move ahead to the correct byte for our bab/for/ref/wil data, read the value, move ahead the rest of the way to the start of the next variable we want to read. So, we move ahead with seekg(+level) from the current position -- if level == 0, then we don't move; if level == 5, we move ahead five.
		Next, we set the bonus.
		Finally, we take 20, which is the most we can skip for a given variable (20 would skip over all the members, as there are twenty of them), minus the length we have already moved, which is our character level, -1 for the block we read. Therefore, we get (20 - 1 - level), or (19-level) as is in the code.


		*/

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
		for (int i = 0; i < 35; i++) {
			flagBuffer[i] = (bool*)readU8(file);
		}
		class_obj->setClassSkillFlag(flagBuffer);

		// read name
		class_obj->setName(readString(file));
	}
	else {
		*err = "error: incorrect file type!";
		return;
	}
}