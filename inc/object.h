#ifndef __OBJ__
#define __OBJ__

#include "ray.h"
#include "vec3.h"
#include "material.h"

struct HitRecord {
	double t;
	Point3 p;
	Color c;
	Vec3 n; // normal
};

class Object {
public:
	Material mat = Material(Vec3(0, 0, 0));
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	virtual Color getColor() = 0;
	Object(Color matt) { mat = Material(matt); }
};


#endif