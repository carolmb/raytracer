#ifndef __OBJ__
#define __OBJ__

#include "ray.h"
#include "vec3.h"
#include "material.h"

struct HitRecord {
	double t;
	Point3 p;
	Material m;
	Vec3 n; // normal
};

class Object {
public:
	Material mat = Material();
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	virtual Material getMaterial() = 0;
	Object(Material mat) mat(mat) {}
};


#endif