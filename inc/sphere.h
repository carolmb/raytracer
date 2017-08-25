#ifndef __SPHERE__
#define __SPHERE__

#include "ray.h"

class Sphere {
public:
	Point3 center;
	double radius;
	Sphere() : center(Point3(0, 1, -1)), radius(0.5) {}

	bool hit(Ray r) {
		Vec3 oc = r.origin() - center;
		double a = r.dir().len2();
		double b = 2.0 * oc.dot(r.dir());
		double c = oc.len2() - (radius*radius);
		return b*b > 4*a*c;
	}
};


#endif