#ifndef PARSER__
#define PARSER__

#include <string>
#include <sstream>
#include "vec3.h"

class Parser {
public:
	bool checkFieldName(std::istringstream &reader, std::string field);
	bool readVec3(std::istringstream &reader, Vec3 &a);
};

#endif