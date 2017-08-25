#ifndef __SPHERE__
#define __SPHERE__

#include <cmath>
#include "object.h"

class Sphere : public Object {
public:
	Point3 center;
	double radius;
	Sphere() : center(Point3(0, 0, -1)), radius(0.5) {}

	double hit(Ray r) {
		Vec3 oc = r.origin() - center;
		double a = r.dir().len2();
		double b = 2.0 * oc.dot(r.dir());
		double c = oc.len2() - (radius*radius);
		double delta = b*b - 4*a*c;
		if(delta > 0) {
			return (-b - std::sqrt(delta)) / (2*a);
		} else {
			return -1;
		}
	}

	Color getColor(Point3 p) {
		Vec3 normal = (p - center).norm();
		return (normal + 1)*0.5;
	}

	~Sphere() {}
};


#endif