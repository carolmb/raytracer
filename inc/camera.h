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
	double distance; // lower left corner
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 w;

public:	
	PerspectiveCamera() : Camera(), origin(), 
		horizontal(Vec3(4, 0, 0)), vertical(Vec3(0, 2, 0)) {}

	PerspectiveCamera(Point3 o, double d, Vec3 h, Vec3 v, Vec3 w) : origin(o), distance(d), horizontal(h), vertical(v), w(w) {}

	Ray getRay(double u, double v) {
		return Ray(origin, horizontal*u + vertical*v - w*distance);
	}

	Point3 getOrigin() { return origin; }

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
