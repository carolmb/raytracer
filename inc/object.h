#ifndef OBJ__
#define OBJ__

#include "hitrecord.h"
#include "material.h"
#include "materials/blinnphongmat.h"

class Object {
public:
	Material *mat;
	virtual bool hit(Ray r, HitRecord &hit, double &mint) = 0;
	Object(Material *mat) : mat(mat) {}
	Object() { mat = new BlinnPhongMaterial(); }
};


#endif