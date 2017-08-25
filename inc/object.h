#ifndef __OBJ__
#define __OBJ__

#include "ray.h"
#include "vec3.h"

class Object {
public:
	virtual double hit(Ray r) = 0;
	virtual Color getColor(Point3 p) = 0;
};


#endif