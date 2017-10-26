#ifndef BPMAT__
#define BPMAT__

#include "material.h"

class BlinnPhongMaterial : public Material {
public:
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	double exps;

	BlinnPhongMaterial(Vec3 ka, Vec3 kd, Vec3 ks, double exps) : ka(ka), kd(kd), ks(ks), exps(exps) {}
	BlinnPhongMaterial() {}
	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) { return false; }
};

#endif
