#ifndef MAT__
#define MAT__

#include "util/vec3.h"
#include "hitrecord.h"
#include <iostream>
#include <string>

class Material {
public:
	virtual bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) = 0;
	virtual Vec3 emitted(double u, double v, Vec3 p) { return Vec3(0, 0, 0); }
};

#endif
