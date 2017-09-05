#ifndef MAT__
#define MAT__

#include "vec3.h"

struct Material {
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	double exps;
	Material(Vec3 ka, Vec3 kd, Vec3 ks, double exps) : ka(ka), kd(kd), ks(ks), exps(exps) {}
	Material() {}
};

#endif