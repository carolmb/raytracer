#include "objs/triangle.h"

#define epsilon 0.0001

#include <cmath>
#include <iostream>

void Triangle::setTransf(Transformation *t) {
	p1 = t->mat*p1;
	p2 = t->mat*p2;
	p3 = t->mat*p3;;
	transf = t;
	edge1 = p2 - p1;
	edge2 = p3 - p1;
	normal = edge1.cross(edge2).norm();
}

bool Triangle::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	
	Vec3 rayDir = ray.dir();
	Vec3 pvec = rayDir.cross(edge2);
	double det = edge1.dot(pvec);
	
	double t;

	if(culling) {
		if(det < epsilon) {
			return false;
		}

		Vec3 tvec = (ray.origin() - p1);
		double u = tvec.dot(pvec);

		if(u < 0 || u > det) {
			return false;
		}

		Vec3 qvec = (tvec.cross(edge1));
		double v = rayDir.dot(qvec);

		if(v < 0 || u + v > det) {
			return false;
		}

		t = edge2.dot(qvec);
		double inv_det = 1/det;

		t *= inv_det;
	} else {

		if(det < epsilon && det > -epsilon) {
			return false;
		}

		double inv_det = 1/det;

		Vec3 tvec = (ray.origin() - p1);
		double u = tvec.dot(pvec) * inv_det;

		if(u < 0 || u > 1) {
			return false;
		}

		Vec3 qvec = (tvec.cross(edge1));
		double v = rayDir.dot(qvec) * inv_det;

		if(v < 0 || u + v > 1) {
			return false;
		}

		t = edge2.dot(qvec);
	}
	
	if(t > maxt){
		return false;
	}

	if(t < mint){
		mint = t;
		hit.t = t;	
		hit.p = ray.at(t);
		hit.n = normal;
		hit.m = idMat;
		return true;
	}
	return false;
}
