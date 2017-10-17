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
	double distance; 
	double halfWidth, halfHeight;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 w;

public:	
	PerspectiveCamera() : Camera(), origin(), 
		horizontal(Vec3(4, 0, 0)), vertical(Vec3(0, 2, 0)) {}

	PerspectiveCamera(Point3 o, double d, Vec3 h, Vec3 v, Vec3 w, double hh, double hw) : 
		origin(o), distance(d), horizontal(h), vertical(v), w(w), halfWidth(hw), halfHeight(hh) {}

	Ray getRay(double u, double v) {
		v = -halfWidth + 2*halfWidth*v;
		u = -halfHeight + 2*halfHeight*u;
		return Ray(origin, horizontal*u + vertical*v - w*distance);
	}

	Point3 getOrigin() { return origin; }

};

class ParallelCamera : public Camera {
	Vec3 u_, v_, w_;
	Point3 e;
	Point3 origin;
	double b, t, l, r;

public:	
	ParallelCamera(Vec3 u, Vec3 v, Vec3 w, Point3 e, double b, double t, double l, double r) : 
		Camera(), u_(u), v_(v), w_(w), e(e), b(b), l(l), r(r) {}

	Ray getRay(double u, double v) {
		u = l + (r - l) * u;
		v = b + (t - b) * v;
		origin = e + u_ * u + v_ * v;
		return Ray(origin, -w_);
	}

	Point3 getOrigin() { return origin; }

};

#endif
