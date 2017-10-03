#ifndef MATPARSER__
#define MATPARSER__

#include "parser.h"
#include "../material.h"

#include <sstream>

class MaterialParser : public Parser {
public:
	bool getMaterial(std::istringstream &reader, Material **mat);
};


	
#endif