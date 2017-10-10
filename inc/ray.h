#ifndef RAY__
#define RAY__

#include "vec3.h"
#include <cmath>
#include <iostream> 
#include <limits>

class Ray {
	Point3 o;
	Vec3 d;

public:
	Ray() : o(), d() {}
	Ray(Point3 o, Vec3 d) : o(o), d(d) {}

	Point3 origin() { return o; }
	Vec3 dir() { return d; }
	Point3 at(double t) { return o + d*t; }
	double getT(Point3 p) { 
		double a = (p - o).x/d.x;
		double b = (p - o).y/d.y;
		double c = (p - o).z/d.z; 
		if (std::abs(a - b) < 0.1 && std::abs(a - c) < 0.1) {
			return a;
		}
		return std::numeric_limits<float>::max();

	} 
};


#endif