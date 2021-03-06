#include "objs/sphere.h"

#include <cmath>
#include <iostream>

#define pi 3.1415

void Sphere::setTransf(Transformation *t) {
	t->mat = t->mat*(Mat4::translation(center)*Mat4::scaling(Vec3(radius, radius, radius))); 
	t->inv = t->mat.inverse();
	transf = t;
}

bool Sphere::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	Vec3 origin = transf->inv*ray.origin();
	Vec3 dir = transf->inv.transfVec(ray.dir());
	Ray newRay(origin, dir);

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
			Vec3 normal = newRay.at(r1).norm();
			hit.n = transf->mat.transfVec(normal).norm();
			hit.m = idMat;
			getUV((hit.p - center)/radius, hit.u, hit.v);
			return true;
		}
		double r2 = (-b + std::sqrt(delta)) / (2*a);
		if(r2 > 0.001 && r2 < mint && r2 < maxt) {
			mint = r2;
			hit.t = r2;
			hit.p = ray.at(r2);
			Vec3 normal = newRay.at(r2).norm();
			hit.n = transf->mat.transfVec(normal).norm();
			getUV((hit.p - center)/radius, hit.u, hit.v);
			hit.m = idMat;
			return true;
		}
	} 
	return false;
}

void Sphere::getUV(Vec3 p, float &u, float &v) {
	float phi = std::atan2(p.z, p.x);
	float theta = std::asin(p.y);
	u = 1 - (phi + pi)/ (2*pi);
	v = (theta + pi/2)/pi;
}
