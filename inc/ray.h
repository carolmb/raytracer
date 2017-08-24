#ifndef __Ray__
#define __Ray__

#include "vec3.h"

class Ray {
	Point3 origin;
	Vec3 dir;

public:
	Ray() : origin(), dir() {}
	Ray(Point3 o, Vec3 d) : origin(o), dir(d) {}

	Point3 getOrigin() { return origin; }
	Vec3 getDir() { return dir; }
	Point3 getPointAt(double t) { return origin + dir*t; } 
};


#endif