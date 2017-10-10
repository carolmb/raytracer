#ifndef DIRLIGHT__
#define DIRLIGHT__

#include "light.h"

#include <limits>

class DiretionalLight : public Light {
	Vec3 dir;
public:
	DiretionalLight(Vec3 dir, Vec3 i) : Light(i), dir(dir.norm()) {} 
	Vec3 getDir(Point3 p = Vec3()) { return -dir; }
	Vec3 getOrigin() { 
		return Vec3(std::numeric_limits<float>::max(), 
					std::numeric_limits<float>::max(), std::numeric_limits<float>::max()); 
	}
};

#endif