#ifndef SPHERE__
#define SPHERE__

#include "objs/object.h"

class Sphere : public Object {
public:
	Point3 center;
	double radius;
	Sphere() : Object() {}
	Sphere(Point3 c, double r, std::string idMat, Transformation *t) : 
		center(c), radius(r), Object(idMat, t) {
			setTransf(t);
		}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation *t);
	void getUV(Vec3 vec, float &u, float &v);
};


#endif