#ifndef LIGHT__
#define LIGHT__

#include "vec3.h"

class Light {
public:
	Vec3 i;
	Light(Vec3 i) : i(i) {}
	virtual Vec3 getDir(Point p = Vec3(0, 0, 0)) = 0;
};

class DiretionalLight : public Light {
	Vec3 dir;
public:
	DiretionalLight(Vec3 dir, Vec3 i) : Light(i), dir(dir) {} 
	Vec3 getDir(Point p = Vec3(0, 0, 0)) { return dir; }
};

#endif
