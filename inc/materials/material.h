#ifndef MAT__
#define MAT__

#include "util/vec3.h"
#include "hitrecord.h"
#include <iostream>

class Material {
public:
	virtual bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) = 0;
};

#endif
