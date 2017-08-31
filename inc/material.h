#ifndef __MAT__
#define __MAT__

class Material {
public:
	Vec3 kd;
	Vec3 ks;
	Vec3 ka;
	Material(Vec3 m) : kd(m) { ks = Vec3(1, 1, 1); ka = Vec3(0.1, 0, 0); }
	Material() { ks = Vec3(1, 1, 1); ka = Vec3(0.1, 0, 0); }
};

#endif