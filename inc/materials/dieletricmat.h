#ifndef DIELETRICMAT__
#define DIELETRICMAT__

#include "materials/material.h"
#include <random>
#include <cmath>
#include <limits>
#include "textures/texture.h"

class DieletricMaterial : public Material {
public:
	Texture *texture;
	double n1;
	double n2;
	static std::knuth_b randomGenerator;

	DieletricMaterial(double n1, double n2) : texture(nullptr), n1(n1), n2(n2) {}

	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) {
		double cosI = -rec.n.dot(r.dir());
		Vec3 reflected = reflect(rec.n, r.dir(), cosI);
		
		att = Vec3(1, 1, 1);
		
		Vec3 refracted;
		bool isRefracted = refract(rec.n, r.dir(), cosI, refracted);
		
		double reflect_prob;
		if(isRefracted) {
			reflect_prob = schlick(rec.n, r.dir(), cosI);
		} else {
			reflect_prob = 1.0;
		}
		float rand = std::generate_canonical<double, std::numeric_limits<double>::digits> (randomGenerator);
		if(rand < reflect_prob) {
			scattered = Ray(rec.p, reflected);
		} else {
			scattered = Ray(rec.p, refracted);
		}
		return true;
	}

	Vec3 reflect(Vec3 normal, Vec3 incident, double cos) {
		return incident + normal * cos * 2;
	}

	bool refract(Vec3 normal, Vec3 incident, double cosI, Vec3 &result) {
		double n = n1/n2;
		double sin = (1 - cosI * cosI) * n * n;
		if(sin > 1) {
			return false;
		}
		double cosT = std::sqrt(1 - sin);
		result = incident * normal * n * (n * cosI - cosT);
		return true;
	}

	double schlick(Vec3 normal, Vec3 incident, double cos) {
		double r0 = (n1 - n2) / (n1 + n2);
		r0 = r0 * r0;
		if(n1 > n2) {
			double n = n1/n2;
			double sinT = n * n * (1 - cos * cos);
			if(sinT > 1.0) return 1.0;
			cos = std::sqrt(1 - sinT);
		}
		double x = 1 - cos;
		return r0 + (1 - r0) * x * x * x * x;
	}
};

std::knuth_b DieletricMaterial::randomGenerator(3);

#endif