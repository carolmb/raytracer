#ifndef SHADERPARSER__
#define SHADERPARSER__

#include "parsers/parser.h"
#include "package.h"
#include <sstream>

class ShaderParser : public Parser {
public:
	bool getShader(std::istringstream &reader, Package *p);
};

#endif