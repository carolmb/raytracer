#include "objs/plane.h"

#include <cmath>
#include <iostream>

#define MIN 0.00001

void Plane::setTransf(Transformation t) {
	origin = t.mat*origin;
	normal = t.mat.transfVec(normal);
	normal = normal.norm();
}

bool Plane::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	double denom = normal.dot(ray.dir().norm());
	if(denom < 0) {
		Vec3 planeOrayO = (origin - ray.origin()).norm();
		double t = planeOrayO.dot(normal)/denom;
		if(t >= 0) {
			if(t < maxt && t < mint) {
				mint = t;
				hit.t = t;
				hit.p = ray.at(t);
				hit.p += normal*MIN;
				hit.n = normal;
				hit.m = mat;
				return true;
			}
		}
	} 
	return false;
}
