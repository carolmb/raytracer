#ifndef RAY__
#define RAY__

#include "vec3.h"
#include <random>

class Ray {
	Point3 o;
	Vec3 d;
	double ap; // aperture
public:
	Ray() : o(), d() {}
	Ray(Point3 o, Vec3 d, double ap = 0) : o(o), d(d), ap(ap) {
		std::knuth_b randomGenerator(3);		
		double deltaX = std::generate_canonical<double, 6>(randomGenerator);
		double deltaY = std::generate_canonical<double, 6>(randomGenerator);		
		o.x = o.x + deltaX * ap - ap/2;
		o.y = o.y + deltaY * ap - ap/2;
	}

	Point3 origin() { return o; }
	Vec3 dir() { return d; }
	Point3 at(double t) { return o + d*t; } 
};


#endif
