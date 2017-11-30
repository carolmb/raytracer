#ifndef HITRECORD__
#define HITRECORD__

#include "ray.h"
#include "util/vec3.h"
#include <memory>
#include <string>

class Material;

// Informations about a hit
struct HitRecord {
	double t;
	Point3 p;
	std::string m;
	Vec3 n; // normal
};

#endif