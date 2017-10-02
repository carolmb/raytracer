#ifndef INPUT__
#define INPUT__

#include <string>

#include "vec3.h"
#include "light.h"
#include "camera.h"
#include "object.h"
#include "package.h"

class Input {
public:
	// Read an input and returns all settings that the render will use
	static Package* readInput(std::string filename);

};

#endif
