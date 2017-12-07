#ifndef MAT__
#define MAT__

#include "util/vec3.h"
#include "hitrecord.h"
#include <iostream>
#include <string>

class Material {
public:
	virtual bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) = 0;
	virtual Vec3 emitted(float u, float v, Vec3 p) = 0;
};

#endif
