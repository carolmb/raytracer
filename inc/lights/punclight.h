#ifndef POINTLIGHT__
#define POINTLIGHT__

#include "lights/light.h"
#include <limits>

class PunctualLight : public Light {
	Point3 o;
public:
	PunctualLight(Vec3 i, Vec3 o) : Light(i), o(o) {}
	Vec3 getDir(Point3 p = Vec3()) { return (p - o).norm(); }
	Vec3 getOrigin() { return o; }
};

#endif