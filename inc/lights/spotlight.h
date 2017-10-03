#ifndef SPOTLIGHT__
#define SPOTLIGHT__

#include "light.h"

#include <cmath>

class SpotLight : public Light {
	Point3 o;
	double angle;
public:
	SpotLight(Vec3 i, Vec3 o, double a) : Light(i), o(o), angle(std::cos(a)) {}
	Vec3 getDir(Point3 p = Vec3()) { 
		Vec3 lightDir = (o - p).norm(); 
		if(lightDir.dot(-lightDir) < angle) {
			return lightDir;
		} 
		return Vec3();
	}
};

#endif