#ifndef MESH__
#define MESH__

#include "objs/object.h"	

class Mesh : public Object {
public:
	objl::Mesh mesh;
	Mesh() : Object() {}
	Mesh(objl::Mesh mesh, Material *mat) : mesh(mesh), Object(mat) {}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation t);
};


#endif