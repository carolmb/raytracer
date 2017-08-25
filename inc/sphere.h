#ifndef __SPHERE__
#define __SPHERE__

#include <cmath>
#include "object.h"

class Sphere : public Object {
public:
	Point3 center;
	double radius;
	Sphere() : center(Point3(0, 0, -1)), radius(0.5) {}
	Sphere(Point3 c, double r) : center(c), radius(r) {}

	bool hit(Ray ray, HitRecord &hit, double &mint) {
		Vec3 oc = ray.origin() - center;
		double a = ray.dir().len2();
		double b = 2.0 * oc.dot(ray.dir());
		double c = oc.len2() - (radius*radius);
		double delta = b*b - 4*a*c;
		if(delta > 0) {
			double r1 = (-b - std::sqrt(delta)) / (2*a);
			if(r1 > 0 && r1 < mint) {
				mint = r1;
				hit.t = r1;
				hit.p = ray.at(r1);
				hit.c = getColor(hit.p);
				return true;
			}
			double r2 = (-b + std::sqrt(delta)) / (2*a);
			if(r2 > 0 && r2 < mint) {
				mint = r2;
				hit.t = r2;
				hit.p = ray.at(r2);
				hit.c = getColor(hit.p);
				return true;
			}
		} 
		return false;
	}

	Color getColor(Point3 p) {
		Vec3 normal = (p - center).norm();
		return (normal + 1)*0.5;
	}

	~Sphere() {}
};


#endif