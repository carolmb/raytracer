#include "sphere.h"

#include <cmath>
#include <iostream>
bool Sphere::hit(Ray ray, HitRecord &hit, double &mint) {
	Vec3 oc = ray.origin() - center;
	double a = ray.dir().len2();
	double b = 2.0 * oc.dot(ray.dir());
	double c = oc.len2() - (radius*radius);
	double delta = b*b - 4*a*c;
	if(delta > 0) {
		double r1 = (-b - std::sqrt(delta)) / (2*a);
		if(r1 > 0.001 && r1 < mint) {
			mint = r1;
			hit.t = r1;
			hit.p = ray.at(r1);
			hit.n = (hit.p - center).norm();
			hit.m = mat;
			return true;
		}
		double r2 = (-b + std::sqrt(delta)) / (2*a);
		if(r2 > 0.001 && r2 < mint) {
			mint = r2;
			hit.t = r2;
			hit.p = ray.at(r2);
			hit.n = (hit.p - center).norm();
			hit.m = mat;
			return true;
		}
	} 
	return false;
}
