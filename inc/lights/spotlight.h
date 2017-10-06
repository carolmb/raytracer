#ifndef SPOTLIGHT__
#define SPOTLIGHT__

#include "light.h"
#include "ray.h"

#include <cmath>
#include <iostream>
#define PI 3.14159265

class SpotLight : public Light {
	Point3 o;
	double angle;
	Vec3 dir;
public:
	SpotLight(Vec3 i, Vec3 o, Vec3 d, double a) : Light(i), o(o), dir(d), angle(std::cos(a*PI / 180.0)) {
		//std::cout << angle << " ";
	}
	Vec3 getDir(Point3 p = Vec3()) { 
		Vec3 lightRay = (p - o).norm(); 
		double currentCos = lightRay.dot(dir.norm());
		if(currentCos > angle) {
			return lightRay;
		} 
		return Vec3();
	}
};

#endif
