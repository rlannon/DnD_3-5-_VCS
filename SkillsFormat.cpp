#include "SkillsFormat.h"
#include "FundamentalDataTypes.h"

void saveSkillStructure(std::ostream& file, Skill skill_structure[35]) {
	// write header and version
	char * header = "SKILLSf";
	file.write(header, 7);
	writeU8(file, skill_version);

	// write skill_structure data
	for (int i = 0; i < 35; i++) {
		writeString(file, skill_structure[i].name);
		writeString(file, skill_structure[i].ability);

		writeU8(file, skill_structure[i].is_general);

		std::cout << skill_structure[i].name << ", " << skill_structure[i].ability << ", " << skill_structure[i].is_general << std::endl;
	}
}

void loadSkillStructure(std::istream& file, Skill * skill_structure, std::string* err) {
	// load header and version
	char header[7];
	char * buffer = header;
	uint8_t vers;

	file.read(buffer, 7);

	if (header[0, 1, 2, 3, 4, 5, 6] == *"S", "K", "I", "L", "L", "S", "f") {
		std::cout << "successfully opened file" << std::endl;
		// code here
		vers = readU8(file);
		
		// potential version control code here

		for (int i = 0; i < 35; i++) {
			(skill_structure+i)->name = readString(file);
			(skill_structure+i)->ability = readString(file);

			(skill_structure+i)->is_general = readU8(file);
		}

		*err = "no errors!";
	}
	else {
		*err = "error: incorrect file format";
	}
}