#ifndef AMBLIGHT__
#define AMBLIGHT__

#include "light.h"

class AmbientLight : public Light {
public:
	AmbientLight(Vec3 i) : Light(i) {}
	AmbientLight() : Light(Vec3()) {}
	Vec3 getDir(Point3 p = Vec3()) { return Vec3(); }
	Vec3 getOrigin() { return Vec3(); }
};

#endif