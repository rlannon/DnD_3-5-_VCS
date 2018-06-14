#pragma once
#include "stdafx.h"

/*

This header lays out all of the necessary functions for writing and reading RVC, VCS, and SKILLS files. It establishes our fundamental data types and functions for reading/writing those types to binary files.
This header only needs to be included in the .cpp files for a file format specification; the header files shouldn't need any of these functions.

Note that these functions are used for reading and writing *unsigned* 8/16 bit values; for signed values, simply cast the signed integer to an unsigned value before writing and cast back to a signed value after reading.

Included here also also functions for returning the proper data path; this is by default set to data/ but having one place to change it makes it easier for future changes in library hierarchy.

*/

// We need readU8 and writeU8 because of the terminator character -- we can't simply read or write 1 byte with file.write() and file.read().

uint8_t readU8(std::istream& file);
void writeU8(std::ostream& file, uint8_t val);

uint16_t readU16(std::istream& file);
void writeU16(std::ostream& file, uint16_t val);

uint32_t readU32(std::istream& file);
void writeU32(std::ostream& file, uint32_t val);

// store float as uint8_t, uint16_t, or uint32_t
// This *could* result in a loss of data, but we shouldn't have problems if we use values that are expected in the system and use the functions correctly
uint8_t convertFloat_U8(float n); // converting float to u8 should only be used for percentages or numbers smaller than 2.55
uint16_t convertFloat_U16(float n);
uint32_t convertFloat_U32(float n); // unlike u8 and u16 conversion, the u32 has 4 decimal places precision instead of 2

float convertU8(uint8_t n);
float convertU16(uint16_t n);
float convertU32(uint32_t n);

// Must write the length of the string to the file, then the string data so we know how long our string actually is
// Note the max string length is 2^16, far longer than we will be needing, but we want to be safe
std::string readString(std::istream& file);
void writeString(std::ostream& file, std::string str);

// Data path functions
std::string getDataPath(std::string filename);