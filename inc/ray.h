#ifndef RAY__
#define RAY__

#include "vec3.h"
#include <random>

class Ray {
	Point3 o_;
	Vec3 d_;
	double ap; // aperture
	static std::knuth_b randomGenerator;
public:
	Ray() : o_(), d_() {}
	Ray(Point3 o, Vec3 d) : o_(o), d_(d) {}
	Ray(Point3 o, Vec3 d, double ap) : o_(o), d_(d), ap(ap) {
				
		double deltaX = (std::generate_canonical<double, 6>(randomGenerator) - 0.5)*ap;
		double deltaY = (std::generate_canonical<double, 6>(randomGenerator) - 0.5)*ap;

		o_.x += deltaX;
		o_.y += deltaY;
		d_.x += deltaX;
		d_.y += deltaY;

	}

	Point3 origin() { return o_; }
	Vec3 dir() { return d_; }
	Point3 at(double t) { return o_ + d_*t; } 
};


#endif
