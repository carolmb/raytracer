#ifndef MESH__
#define MESH__

#include "objs/object.h"	

class Mesh : public Object {
public:
	objl::Mesh mesh;
	Mesh() : Object() {}
	Mesh(objl::Mesh mesh, std::string idMat, Transformation *t) : 
		mesh(mesh), Object(idMat, t) {}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation *t);
	Point3 getVerticeInMesh(int index);
};


#endif