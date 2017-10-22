#include "triangle.h"

#define epsilon 0.00001

#include <cmath>
#include <iostream>

bool Triangle::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	Vec3 edge1 = p2 - p1;
	Vec3 edge2 = p3 - p1;
	Vec3 pvec = ray.dir().cross(edge2);
	double det = edge1.dot(pvec);
	if(det < epsilon) {
		return false;
	}

	Vec3 tvec = ray.origin() - p1;
	double u = tvec.dot(pvec);

	if(u < 0 || u > det) {
		return false;
	}

	Vec3 qvec = tvec.cross(edge1);
	double v = ray.dir().dot(qvec);

	if(v < 0 || u + v > det) {
		return false;
	}

	double t = edge2.dot(qvec);
	double inv_det = 1/det;

	t *= inv_det;
	u *= inv_det;
	v *= inv_det;

	if(t > maxt){
		return false;
	}

	if(t < mint){
		t = mint;
		hit.t = t;
		hit.p = ray.at(t);
		hit.n = (p1 - hit.p).cross((p2 - hit.p)).norm();
		hit.m = mat;
		return true;
	}

}
