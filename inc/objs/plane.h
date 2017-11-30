#ifndef PLANE__
#define PLANE__

#include "objs/object.h"

class Plane : public Object {
public:
	Point3 origin;
	Vec3 normal;
	Plane() : Object() {}
	Plane(Point3 o, Vec3 n, std::string idMat, Transformation *t) : 
		origin(o), normal(n), Object(idMat, t) {
			setTransf(t);
		}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation *t);
};


#endif