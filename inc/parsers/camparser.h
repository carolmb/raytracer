#ifndef CAMPARSER__
#define CAMPARSER__

#include "parsers/parser.h"
#include "camera.h"
#include <sstream>

class CameraParser : public Parser {
public:
	bool getCamera(std::istringstream &reader, Camera **cam);
};

#endif