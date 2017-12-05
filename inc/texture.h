#ifndef TEXTURE__
#define TEXTURE__

#include "util/vec3.h"

class texture {
public:
	virtual Vec3 value(float u, float v, Vec3 vec) = 0;
};

#endif