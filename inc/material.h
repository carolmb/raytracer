#ifndef __MAT__
#define __MAT__

class Material {
public:
	Vec3 kd;
	Vec3 ks;
	Vec3 ka;
	Material(Vec3 m) : kd(m) {}
};

#endif