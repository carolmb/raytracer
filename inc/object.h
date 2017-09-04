#ifndef __OBJ__
#define __OBJ__

#include "hitrecord.h"
#include "material.h"

class Object {
public:
	Material mat;
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	virtual Material getMaterial() = 0;
	Object(Material mat) : mat(mat) {}
	Object() { mat = Material(); }
};


#endif