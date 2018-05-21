#include "FundamentalDataTypes.h"

// READ/WRITE UINT8_T

uint8_t readU8(std::istream& file) {
	uint8_t val;
	uint8_t bytes[2];
	file.read((char*)bytes, 1);
	val = bytes[0];
	return val;
}
void writeU8(std::ostream& file, uint8_t val) {
	uint8_t bytes[2];

	bytes[0] = val;

	file.write((char*)bytes, 1);
}

// READ/WRITE UINT16_T

uint16_t readU16(std::istream& file) {
	uint16_t val;
	uint8_t bytes[2];

	file.read((char*)bytes, 2); // read 2 bytes from the file
	val = bytes[0] | (bytes[1] << 8);

	return val;
}
void writeU16(std::ostream& file, uint16_t val) {
	uint8_t bytes[2];

	// extract individual bytes from our 16-bit value
	bytes[0] = (val) & 0xFF;	// low byte
	bytes[1] = (val >> 8) & 0xFF;	// high byte

	file.write((char*)bytes, 2);
}

// READ/WRITE STRING AND STRING LENGTH

std::string readString(std::istream& file) {
	uint16_t len = readU16(file);

	char* buffer = new char[len];
	file.read(buffer, len);

	std::string str(buffer, len);
	delete[] buffer;

	return str;
}
void writeString(std::ostream& file, std::string str) {
	uint16_t len = str.length();

	writeU16(file, len);
	file.write(str.c_str(), len);
}