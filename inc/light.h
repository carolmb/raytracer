#ifndef LIGHT__
#define LIGHT__

#include "vec3.h"

class Light {
public:
	Vec3 i;
	Light(Vec3 i) : i(i) {}
	virtual Vec3 getDir(Point3 p = Vec3()) = 0;
};

class DiretionalLight : public Light {
	Vec3 dir;
public:
	DiretionalLight(Vec3 dir, Vec3 i) : Light(i), dir(dir) {} 
	Vec3 getDir(Point3 p = Vec3()) { return dir; }
};

class AmbientLight : public Light {
public:
	AmbientLight(Vec3 i) : Light(i) {}
	AmbientLight() : Light(Vec3()) {}
	Vec3 getDir(Point3 p = Vec3()) { return Vec3(); }
};

#endif
