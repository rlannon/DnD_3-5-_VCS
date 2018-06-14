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

uint32_t readU32(std::istream& file) {
	uint32_t val;
	uint8_t bytes[4];

	file.read((char*)bytes, 4);
	val = bytes[0] | (bytes[1] << 8) | (bytes[2] << 16) | (bytes[3] << 24);

	return val;
}
void writeU32(std::ostream& file, uint32_t val) {
	uint8_t bytes[4];

	// extract individual bytes from 32-bit value
	bytes[0] = (val) & 0xFF; // lowest
	bytes[1] = (val >> 8) & 0xFF;
	bytes[2] = (val >> 16) & 0xFF;
	bytes[3] = (val >> 24) & 0xFF;

	file.write((char*)bytes, 4);
}

// STORE FLOAT AS U8 OR U16

uint8_t convertFloat_U8(float n) { // U8 should only be used for decimal places of 2 digits with numbers less than 2.55
	float u8 = n; // multiply by 10^1 to store 2 decimal place as an integer
	u8 *= 100;
	return (uint8_t)u8;
}
uint16_t convertFloat_U16(float n) {
	float u16 = n;
	u16 *= 100;
	return (uint16_t)u16;
}
uint32_t convertFloat_U32(float n) { // this is the safer option, as it can store 3 digits
	float u32 = n; // multiply by 10^4 to store 4 decimal places as an integer
	u32 *= 10000;
	return (uint32_t)u32;
}

// STORE U8 OR U16 AS FLOAT

float convertU8(uint8_t n) {
	float u8 = n;
	u8 /= 100;
	return u8;
}
float convertU16(uint16_t n) {
	float u16 = n;
	u16 /= 100;
	return u16;
}
float convertU32(uint32_t n) {
	float u32 = n;
	u32 /= 10000;
	return u32;
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

// DATA PATH STANDARD

std::string getDataPath(std::string filename) {
	return ("data/" + filename);
}
