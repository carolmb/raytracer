#ifndef __OBJ__
#define __OBJ__

#include "ray.h"
#include "vec3.h"
#include "material.h"

struct HitRecord {
	double t;
	Point3 p;
	Color c;
};

class Object {
public:
	Material mat = Material(Vec3(1, 1, 1));
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	virtual Color getColor(Point3 p) = 0;
};


#endif