#ifndef CAMERA__
#define CAMERA__

#include "util/vec3.h"
#include "ray.h"
#include <iostream>

class Camera {
public:	
	Camera() {}
	virtual Ray getRay(double u, double v) = 0;
};

class PerspectiveCamera : public Camera {
	Point3 origin;
	double distance; 
	double halfWidth, halfHeight;
	Vec3 horizontal;
	Vec3 vertical;
	Vec3 w;
	double aperture;
	double fdist;

public:	
	PerspectiveCamera() : Camera(), origin(), 
		horizontal(Vec3(4, 0, 0)), vertical(Vec3(0, 2, 0)) {}

	PerspectiveCamera(Point3 o, double d, Vec3 h, Vec3 v, Vec3 w, 
		double hh, double hw, double ap, double fdist) : 
		origin(o), distance(d), horizontal(h), vertical(v), w(w), 
		halfWidth(hw), halfHeight(hh), aperture(ap), fdist(fdist) {}

	Ray getRay(double u, double v) {
		v = -halfWidth + 2*halfWidth*v;
		u = -halfHeight + 2*halfHeight*u;
		return Ray(origin, horizontal*u + vertical*v - w*distance, aperture, fdist);
	}
};

class ParallelCamera : public Camera {
	Vec3 horizontal, vertical, llc, w;
	Point3 e;
	Point3 origin;
	//double b, t, l, r;

public:	
	ParallelCamera(Vec3 u, Vec3 v, Vec3 w, Point3 e, double b, double t, double l, double r) : 
		Camera(), w(w), e(e)/*, b(b), t(t), l(l), r(r)*/ {
			llc = e + Vec3(l, b, 0);
			horizontal = Vec3(r - l, 0, 0);
			vertical = Vec3(0, t - b, 0);
		}

	Ray getRay(double u, double v) {
		origin = llc + horizontal * u + vertical * v;
		return Ray(origin, -w);
	}
};

#endif
