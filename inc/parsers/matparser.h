#ifndef MATPARSER__
#define MATPARSER__

#include "parsers/parser.h"
#include "materials/material.h"

#include <sstream>
#include <map>

class MaterialParser : public Parser {
public:
	bool getMaterial(std::istringstream &reader, std::map<std::string, std::shared_ptr<Material> > &materials);
	bool getMaterialList(std::istringstream &reader, std::map<std::string, std::shared_ptr<Material> > &materials);
};


	
#endif