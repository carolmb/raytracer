#ifndef HEADERPARSER__
#define HEADERPARSER__

#include "parser.h"
#include "package.h"
#include <sstream>

class HeaderParser : public Parser {
public: 
	bool getHeader(std::istringstream &reader, Package *p);

};


#endif