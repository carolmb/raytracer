#ifndef __MAT__
#define __MAT__

class Material {
public:
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	double exps;
	Material(Vec3 ka, Vec3 kd, Vec3 ks, double exps) : ka(ka), kd(kd), ks(ks), exps(exps) {}
	Material() : {}

#endif