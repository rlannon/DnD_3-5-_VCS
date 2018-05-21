#pragma once
#include "stdafx.h"

/*

This header lays out all of the necessary functions for writing and reading RVC, VCS, and SKILLS files. It establishes our fundamental data types and functions for reading/writing those types to binary files.
This header only needs to be included in the .cpp files for a file format specification; the header files shouldn't need any of these functions.

*/

uint8_t readU8(std::istream& file);
void writeU8(std::ostream& file, uint8_t val);

uint16_t readU16(std::istream& file);
void writeU16(std::ostream& file, uint16_t val);

// Must write the length of the string to the file, then the string data so we know how long our string actually is
// Note the max string length is 2^16, far longer than we will be needing, but we want to be safe
std::string readString(std::istream& file);
void writeString(std::ostream& file, std::string str);