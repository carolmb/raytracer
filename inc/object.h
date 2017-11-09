#ifndef OBJ__
#define OBJ__

#include "hitrecord.h"
#include "material.h"
#include "materials/blinnphongmat.h"
#include "transf.h"

class Object {
public:
	Material *mat;
	Transformation transf;
	virtual bool hit(Ray r, HitRecord &hit, double &mint, double maxt) = 0;
	Object(Material *mat) : mat(mat) {}
	Object() { mat = new BlinnPhongMaterial(); }
	virtual void setTransf(Transformation t) = 0;
};


#endif