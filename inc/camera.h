#ifndef __CAMERA__
#define __CAMERA__

#include "vec3.h"
#include "ray.h"

class Camera {
	Point3 origin;
	Point3 lowerLeftCorner; // lower left corner
	Vec3 horizontal;
	Vec3 vertical;

public:	
	Camera() : origin(), 
		lowerLeftCorner(Vec3(-2, -1, -1)), horizontal(Vec3(4, 0, 0)), vertical(Vec3(0, 2, 0)) {}

	Ray getRay(double u, double v) {
		return Ray(origin, lowerLeftCorner + horizontal*u + vertical*v - origin);
	}

	Point3 getOrigin() { return origin; }

};

#endif