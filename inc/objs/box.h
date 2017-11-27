#ifndef BOX__
#define BOX__

#include "objs/object.h"
#include "objs/triangle.h"

class Box : public Object {
public:
	std::vector<Triangle> triangles;
	Vec3 normal;
	Box() : Object() {}
	Box(Point3 e0, Point3 e7, Material *mat);
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation t);
};


#endif