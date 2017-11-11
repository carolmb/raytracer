#ifndef INPUT__
#define INPUT__

#include <string>

#include "util/vec3.h"
#include "lights/light.h"
#include "camera.h"
#include "objs/object.h"
#include "package.h"

class Input {
public:
	// Read an input and returns all settings that the render will use
	static Package* readInput(std::string filename);

};

#endif
