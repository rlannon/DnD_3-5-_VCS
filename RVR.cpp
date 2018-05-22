#include "FundamentalDataTypes.h"
#include "RVR.h"

void saveToRVR(std::ostream& file, Race race) {
	// write header data
	char * header = "RVRf";
	file.write(header, 4);
	
	//file.write((char*)rvr_version, 1);
	writeU8(file, rvr_version);

	writeString(file, race.name);

	// Our values are signed, but we want to store them as unsigned, so cast form int8_t to uint8_t
	writeU8(file, (uint8_t)race.str_bonus);
	writeU8(file, (uint8_t)race.dex_bonus);
	writeU8(file, (uint8_t)race.con_bonus);
	writeU8(file, (uint8_t)race.int_bonus);
	writeU8(file, (uint8_t)race.wis_bonus);
	writeU8(file, (uint8_t)race.cha_bonus);

	writeString(file, race.known_languages);
}

void loadRVR(std::istream& file, Race* race, std::string* err) {
	char header[4];
	char * buffer = &header[0];
	uint8_t version;

	file.read(buffer, 4);
	if (header[0, 1, 2, 3] == *"R", "V", "R", "f") {
		version = readU8(file);
		// add version control code here, if desired

		race->name = readString(file);

		// Since our values are signed, but stored as unsigned, we must cast back to int8_t
		race->str_bonus = (int8_t)readU8(file);
		race->dex_bonus = (int8_t)readU8(file);
		race->con_bonus = (int8_t)readU8(file);
		race->int_bonus = (int8_t)readU8(file);
		race->wis_bonus = (int8_t)readU8(file);
		race->cha_bonus = (int8_t)readU8(file);

		race->known_languages = readString(file);

		*err = "no errors in RVR file!";
	}
	else {
		*err = "error: incorrect file format! file header does not match \"RVRF\"!";
	}
}