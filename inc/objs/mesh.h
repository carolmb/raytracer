#ifndef MESH__
#define MESH__

#include "objs/object.h"	

class Mesh : public Object {
public:
	objl::Mesh mesh;
	Mesh() : Object() {}
	Mesh(objl::Mesh mesh, Material *mat, Transformation *t) : 
		mesh(mesh), Object(mat, t) {}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation *t);
};


#endif