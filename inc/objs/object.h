#ifndef OBJ__
#define OBJ__

#include "hitrecord.h"
#include "materials/material.h"
#include "materials/blinnphongmat.h"
#include "util/transf.h"
#include <memory>

class Object {
public:
	std::shared_ptr<Material> mat;
	Transformation *transf;
	virtual bool hit(Ray r, HitRecord &hit, double &mint, double maxt) = 0;
	//Object(Material *mat, Transformation *t) : mat(mat), transf(t) {}
	Object(std::shared_ptr<Material> mat, Transformation *t) : mat(mat), transf(t) {}
	
	Object() { mat = std::shared_ptr<Material>(new BlinnPhongMaterial()); }
	virtual void setTransf(Transformation *t) = 0;
};


#endif