#ifndef RAY__
#define RAY__

#include "vec3.h"

class Ray {
	Point3 o;
	Vec3 d;

public:
	Ray() : o(), d() {}
	Ray(Point3 o, Vec3 d) : o(o), d(d) {}

	Point3 origin() { return o; }
	Vec3 dir() { return d; }
	Point3 at(double t) { return o + d*t; } 
};


#endif