#ifndef __HITRECORD__
#define __HITRECORD__

#include "ray.h"
#include "vec3.h"
#include "material.h"

class HitRecord {
public:
	double t;
	Point3 p;
	Material m;
	Vec3 n; // normal
};

#endif