#ifndef POINTLIGHT__
#define POINTLIGHT__

#include "light.h"

class PunctualLight : public Light {
	Point3 o;
public:
	PunctualLight(Vec3 i, Vec3 o) : Light(i), o(o) {}
	Vec3 getDir(Point3 p = Vec3()) { return (o - p).norm(); }
};

#endif