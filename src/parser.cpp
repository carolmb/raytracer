#include "parsers/parser.h"

bool Parser::checkFieldName(std::istringstream &reader, std::string field) {
	std::string f;
	reader >> f;
	if(field.compare(f) != 0) return false;
	reader >> f;
	if(f.compare("=") != 0) return false;
	return true;
}

bool Parser::readVec3(std::istringstream &reader, Vec3 &a) {
 	std::string r, g, b;
 	reader >> r >> g >> b;
 	a.x = std::stod (r);
 	a.y = std::stod (g);
 	a.z = std::stod (b);
	return true;
}
