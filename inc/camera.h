#ifndef CAMERA__
#define CAMERA__

#include "vec3.h"
#include "ray.h"
#include <iostream>

class Camera {
public:	
	Camera() {}
	virtual Ray getRay(double u, double v) = 0;
	virtual Point3 getOrigin() = 0;
};

class PerspectiveCamera : public Camera {
	Point3 origin;
	Point3 lowerLeftCorner; // lower left corner
	Vec3 horizontal;
	Vec3 vertical;

public:	
	PerspectiveCamera() : origin(), 
		lowerLeftCorner(Vec3(-2, -1, -1)), horizontal(Vec3(4, 0, 0)), vertical(Vec3(0, 2, 0)) {}

	PerspectiveCamera(Point3 o, Vec3 llc, Vec3 h, Vec3 v) : origin(o), lowerLeftCorner(llc), horizontal(h), vertical(v) {}

	Ray getRay(double u, double v) {
		return Ray(origin, lowerLeftCorner + horizontal*u + vertical*v - origin);
	}

	Point3 getOrigin() { return origin; }
	Point3 getLLC() { return lowerLeftCorner; }

};

class OrthographicParallelCamera : public Camera {
	Vec3 u, v, w;
	Point3 e;
	Point3 origin;

public:	
	OrthographicParallelCamera(Vec3 u, Vec3 v, Vec3 w, Point3 e) : 
		Camera(), u(u), v(v), w(w), e(e) {}

	Ray getRay(double u, double v) {
		origin = e + this->u * u + this->v * v;
		return Ray(origin, -w);
	}

	Point3 getOrigin() { return origin; }

};

class ObliqueParallelCamera : public Camera {
	Vec3 u, v, w;
	Point3 e;
	Vec3 dir;
	Point3 origin;

public:	
	ObliqueParallelCamera(Vec3 u, Vec3 v, Vec3 w, Point3 e, Vec3 dir) : 
		Camera(), u(u), v(v), w(w), e(e), dir(dir) {}

	Ray getRay(double u, double v) {
		origin = e + this->u * u + this->v * v;
		return Ray(origin, dir);
	}

	Point3 getOrigin() { return origin; }

};

#endif
