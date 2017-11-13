#include "objs/sphere.h"

#include <cmath>
#include <iostream>

void Sphere::setTransf(Transformation t) {
	t.mat = (Mat4::scaling(Vec3(radius, radius, radius)) * Mat4::translation(center)) * t.mat; 
	t.inv = t.mat.inverse();
	transf = t;
}

bool Sphere::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	Vec3 origin = transf.inv*ray.origin();
	Vec3 dir = transf.inv.transfVec(ray.dir());

	double a = dir.len2();
	double b = 2.0 * origin.dot(dir);
	double c = origin.len2() - 1;
	double delta = b*b - 4*a*c;
	if(delta > 0) {
		double r1 = (-b - std::sqrt(delta)) / (2*a);
		if(r1 > 0.001 && r1 < mint && r1 < maxt) {
			mint = r1;
			hit.t = r1;
			hit.p = ray.at(r1);
			hit.n = (transf.mat.transfVec(hit.p - center)).norm();
			hit.m = mat;
			return true;
		}
		double r2 = (-b + std::sqrt(delta)) / (2*a);
		if(r2 > 0.001 && r2 < mint && r2 < maxt) {
			mint = r2;
			hit.t = r2;
			hit.p = ray.at(r2);
			hit.n = (transf.mat.transfVec(hit.p - center)).norm();
			hit.m = mat;
			return true;
		}
	} 
return false;
}
