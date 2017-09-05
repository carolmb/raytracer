#ifndef LIGHT__
#define LIGHT__

#include "vec3.h"

struct Light {
	Vec3 dir;
	Vec3 i;
};

#endif