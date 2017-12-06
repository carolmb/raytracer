#ifndef DIELETRICMAT__
#define DIELETRICMAT__

#include "materials/material.h"
#include <random>
#include <cmath>
#include <limits>
#include "textures/texture.h"

class DieletricMaterial : public Material {
public:
	double ref;
	static std::knuth_b randomGenerator;

	DieletricMaterial(double ref) : ref(ref) {}

	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) {
		Vec3 normalUnit = rec.n;
		Vec3 dirUnit = r.dir();
		double cosI = normalUnit.dot(dirUnit);
		att = Vec3(1, 1, 1);
		Vec3 outwardNormal;
		double n;

		if (cosI > 0) {
			outwardNormal = - rec.n;
			n = ref;
			cosI = cosI*n;
		} else {
			outwardNormal = rec.n;
			n = 1/ref;
			cosI = - cosI;
		}

		Vec3 refracted;
		bool isRefracted = refract(outwardNormal, r.dir(), refracted, n);
		
		double reflect_prob;
		if(isRefracted) {
			reflect_prob = schlick(n, cosI);
		} else {
			reflect_prob = 1.0;
		}

		float rand = std::generate_canonical<double, std::numeric_limits<double>::digits> (randomGenerator);
		if(rand < reflect_prob) {
			Vec3 reflected = reflect(rec.n, r.dir());	
			scattered = Ray(rec.p, reflected);
			return false;
		} else {
			scattered = Ray(rec.p, refracted);
		}
		return true;
	}

	Vec3 reflect(Vec3 normal, Vec3 incident) {
		return incident - normal * normal.dot(incident) * 2;
	}

	bool refract(Vec3 normal, Vec3 incident, Vec3 &result, double n) {
		incident = incident.norm();
		double cos = normal.dot(incident);
		double disc = 1 - n*n*(1 - cos*cos);
		if(disc > 0) {
			result = (incident - normal*cos)*n - normal*std::sqrt(disc);
			return true;
		}
		return false;
	}

	double schlick(double n, double cos) {
		double r0 = (1 - n) / (1 + n);
		r0 = r0 * r0;
		double x = 1 - cos;
		return r0 + (1 - r0) * x * x * x * x * x;
	}
};
std::knuth_b DieletricMaterial::randomGenerator(3);

#endif