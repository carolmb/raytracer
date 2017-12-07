#ifndef LIGHTPARSER__
#define LIGHTPARSER__

#include "parsers/parser.h"
#include "lights/light.h"

#include <sstream>
#include <vector>
#include <memory>	

class LightParser : public Parser {
public:
	bool getLightList(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights);
private:
	bool readLight(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights);
};

#endif