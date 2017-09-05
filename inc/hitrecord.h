#ifndef HITRECORD__
#define HITRECORD__

#include "ray.h"
#include "vec3.h"
#include "material.h"

// Informations about a hit
class HitRecord {
public:
	double t;
	Point3 p;
	Material m;
	Vec3 n; // normal
};

#endif