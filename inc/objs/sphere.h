#ifndef SPHERE__
#define SPHERE__

#include "objs/object.h"

class Sphere : public Object {
public:
	Point3 center;
	double radius;
	Sphere() : Object() {}
	Sphere(Point3 c, double r, std::shared_ptr<Material> mat, Transformation *t) : 
		center(c), radius(r), Object(mat, t) {
			setTransf(t);
		}
	bool hit(Ray ray, HitRecord &hit, double &mint, double maxt);
	void setTransf(Transformation *t);
};


#endif