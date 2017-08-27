#ifndef __OBJ__
#define __OBJ__

#include "ray.h"
#include "vec3.h"

struct HitRecord {
	double t;
	Point3 p;
	Color c;
};

class Object {
public:
	int x;
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	virtual Color getColor(Point3 p) = 0;
};


#endif