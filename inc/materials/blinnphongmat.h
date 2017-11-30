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
	BlinnPhongMaterial(objl::Material meshMat) {
		ka = Vec3(meshMat.Ka.X, meshMat.Ka.Y, meshMat.Ka.Z);
		kd = Vec3(meshMat.Kd.X, meshMat.Kd.Y, meshMat.Kd.Z);
		ks = Vec3(meshMat.Ks.X, meshMat.Ks.Y, meshMat.Ks.Z);
		exps = meshMat.Ns;
	}

	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) { return false; }
};

#endif
