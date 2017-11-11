#ifndef MATPARSER__
#define MATPARSER__

#include "parsers/parser.h"
#include "materials/material.h"

#include <sstream>

class MaterialParser : public Parser {
public:
	bool getMaterial(std::istringstream &reader, Material **mat);
};


	
#endif