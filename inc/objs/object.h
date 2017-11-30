#ifndef OBJ__
#define OBJ__

#include "hitrecord.h"
#include "materials/material.h"
#include "materials/blinnphongmat.h"
#include "util/transf.h"
#include <memory>

class Object {
public:
	std::string idMat;
	Transformation *transf;
	virtual bool hit(Ray r, HitRecord &hit, double &mint, double maxt) = 0;
	//Object(Material *mat, Transformation *t) : mat(mat), transf(t) {}
	Object(std::string mat, Transformation *t) : idMat(mat), transf(t) {}
	
	Object() { idMat = "default"; transf = nullptr; }
	virtual void setTransf(Transformation *t) = 0;
};


#endif