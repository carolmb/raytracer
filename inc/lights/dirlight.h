#ifndef DIRLIGHT__
#define DIRLIGHT__

#include "light.h"

class DiretionalLight : public Light {
	Vec3 dir;
public:
	DiretionalLight(Vec3 dir, Vec3 i) : Light(i), dir(dir.norm()) {} 
	Vec3 getDir(Point3 p = Vec3()) { return -dir; }
};

#endif