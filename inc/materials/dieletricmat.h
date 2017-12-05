#ifndef DIELETRICMAT__
#define DIELETRICMAT__

#include "materials/material.h"
#include <random>
#include "textures/texture.h"

class DieletricMaterial : public Material {
public:
	std::knuth_b randomGenerator;
	Texture *texture;
	double n1;
	double n2;

	DieletricMaterial(double n1, double n2) : texture(nullptr), n1(n1), n2(n2) {}

	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) {
		Vec3 reflected = reflect(rec.n, r.dir());
		float ni_over_nt;
		att = Vec3(1, 1, 1);
		Vec3 refracted;
		bool isRefracted = refract(rec.n, r.dir(), refracted);
		if(isRefracted) {
			scattered = Ray(rec.p, refracted);
			return false;
		} else {
			scattered = Ray(rec.p, reflected);
		}
		return true;
	}

	Vec3 reflect(Vec3 normal, Vec3 incident) {
		double cos = -normal.dot(incident); // VERIFICAR SE OS VETORES ESTÃO NORM
		return incident + normal * cos * 2;
	}

	bool refract(Vec3 normal, Vec3 incident, Vec3 &result) {
		double n = n1/n2;
		double cosI = -normal.dot(incident);
		double sin = (1 - cosI * cosI) * n * n;
		if(sin > 1) {
			return false;
		}
		double cosT = std::sqrt(1 - sin);
		result = incident * normal * n * (n * cosI - cosT);
		return true;
	}

	/*double reflectance(Vec3 normal, Vec3 incident) {
		double n = n1/n2;
		double cosI = -normal.double(incident);
		double sin = (1 - cos*cos) * n * n;
		if(sin > 1) {
			return Vec(std::nan, std::nan, std::nan);
		}
		double cosT = std::sqrt(1 - sin);
		double r0rth = (n1 * cosI - n2 * cosT) / (n1 * cosI + n2 *cosT);
		double rPar = (n2 * cosI - n1 * cosT) / (n2 * cosI + n1 * cosT);
		return (r0rth * r0rth + rPar * rPar) / 2.0; 	
	}*/
};

#endif