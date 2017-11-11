#ifndef HITRECORD__
#define HITRECORD__

#include "ray.h"
#include "util/vec3.h"

class Material;

// Informations about a hit
struct HitRecord {
	double t;
	Point3 p;
	Material *m;
	Vec3 n; // normal
};

#endif