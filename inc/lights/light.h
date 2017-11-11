#ifndef LIGHT__
#define LIGHT__

#include "util/vec3.h"

class Light {
public:
	Vec3 i;
	Light(Vec3 i) : i(i) {}
	virtual Vec3 getDir(Point3 p = Vec3()) = 0;
	virtual Vec3 getOrigin() = 0;
};

#endif
