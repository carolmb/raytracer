#ifndef DIFFUSELIGHT__
#define DIFFUSELIGHT__

#include "material.h"
#include "textures/texture.h"


class DiffuseLightMaterial : public Material {
	Texture *emit; 
public:
	DiffuseLightMaterial(Texture *emit) : emit(emit) {}
	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) {
		return false;
	}
	Vec3 emitted(float u, float v, Vec3 p) {
		return emit->value(u, v, p);
	}
};


#endif