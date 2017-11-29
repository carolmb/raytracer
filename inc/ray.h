#ifndef RAY__
#define RAY__

#include "util/vec3.h"

#include <cmath>
#include <iostream> 
#include <limits>
#include <random>


class Ray {
	Point3 o_;
	Vec3 d_;
	double ap; // aperture
	static std::knuth_b randomGenerator;
public:
	Ray() : o_(), d_() { d_ = d_.norm(); }
	Ray(Point3 o, Vec3 d) : o_(o), d_(d) {}
	Ray(Point3 o, Vec3 d, double ap, double focaldist) : o_(o), d_(d), ap(ap) {
		if(ap > 0) {		
			Vec3 v;
	      	do{
		        double x = std::generate_canonical<double, std::numeric_limits<double>::digits> (randomGenerator);
		        double y = std::generate_canonical<double, std::numeric_limits<double>::digits> (randomGenerator);
		        v = Vec3(x,y,0)*2 - Vec3(1,1,0);
	      	} while(v.dot(v) >= 1.0);

			double t = -focaldist/d.z;
			Point3 pfocus = at(t);
			
			o_ = o_ + v*ap;
			d_ = (pfocus - o_).norm();
		} 
		d_ = d_.norm();
	}

	double getT(Point3 p) { 
		double a = (p - o_).x/d_.x;
		double b = (p - o_).y/d_.y;
		double c = (p - o_).z/d_.z; 
		if (std::abs(a - b) < 0.1 && std::abs(a - c) < 0.1) {
			return a;
		}
		return std::numeric_limits<float>::max();

	}

	Point3 origin() { return o_; }
	Vec3 dir() { return d_; }
	Point3 at(double t) { return o_ + d_*t; } 

};


#endif
