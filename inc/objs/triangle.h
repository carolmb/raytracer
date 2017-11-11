#ifndef TRIANGLE__
#define TRIANGLE__

#include "objs/object.h"

class Triangle : public Object {
public:
	Point3 p1, p2, p3;
	Triangle() : Object() {}
	Triangle(Point3 p1, Point3 p2, Point3 p3, Material *mat) : p1(p1), p2(p2), p3(p3), Object(mat) {}

	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation t);
};


#endif