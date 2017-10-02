#ifndef SCENEPARSER__
#define SCENEPARSER__

#include "parser.h"
#include "package.h"

class SceneParser : public Parser {
public:
	bool getScene(std::istringstream &reader, Package *p);
};

#endif