#ifndef SPOTLIGHT__
#define SPOTLIGHT__

#include "lights/light.h"
#include "ray.h"

#include <cmath>
#include <iostream>
#define PI 3.14159265

class SpotLight : public Light {
	Point3 o;
	double angle;
	Vec3 dir;
	double exp = 0.5; // TODO read from file
public:
	SpotLight(Vec3 i, Vec3 o, Vec3 d, double a) : 
		Light(i), o(o), dir(d.norm()), angle(std::cos(a*PI / 180.0)) {}

	Vec3 getDir(Point3 p = Vec3()) { 
		Vec3 lightRay = (p - o).norm(); 
		double currentCos = lightRay.dot(dir);
		if(currentCos > angle) {
			double att = currentCos*currentCos*exp;
			return lightRay * att;
		} 
		return Vec3();
	}

	Vec3 getOrigin() {
		return o;
	}
};

#endif
