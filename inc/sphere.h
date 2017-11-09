#ifndef SPHERE__
#define SPHERE__

#include "object.h"

class Sphere : public Object {
public:
	Point3 center;
	double radius;
	Sphere() : Object() {}
	Sphere(Point3 c, double r, Material *mat) : center(c), radius(r), Object(mat) {}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation t);
};


#endif