#ifndef BPMAT__
#define BPMAT__

#include "materials/material.h"
#include "util/OBJ_Loader.h"


class BlinnPhongMaterial : public Material {
public:
	Vec3 ka;
	Vec3 kd;
	Vec3 ks;
	double exps;

	BlinnPhongMaterial(Vec3 ka, Vec3 kd, Vec3 ks, double exps) : ka(ka), kd(kd), ks(ks), exps(exps) {}
	BlinnPhongMaterial(objl::Material meshMat) {}
	BlinnPhongMaterial() {}
	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) { return false; }
};

#endif
