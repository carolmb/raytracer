#ifndef DIELECTRICMAT__
#define DIELECTRICMAT__

#include "materials/material.h"
#include <random>
#include <cmath>
#include <limits>
#include "textures/texture.h"

class DielectricMaterial : public Material {
public:
	double ref;
	static std::knuth_b randomGenerator;

	DielectricMaterial(double ref) : ref(ref) {}

	Vec3 emitted(float u, float v, Vec3 p) { return Vec3(); }

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
			cosI = std::sqrt(1 - n*n*(1 - cosI*cosI));
			//cosI = cosI*n;
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

		float rand = std::generate_canonical<double, 9> (randomGenerator);
		Vec3 origin = rec.p - outwardNormal * 0.001;
		if(rand < reflect_prob) {
			Vec3 reflected = reflect(rec.n, r.dir());	
			scattered = Ray(origin, reflected);
			// return false;
		} else {
			scattered = Ray(origin, refracted);
		}
		return true;
	}

	Vec3 reflect(Vec3 normal, Vec3 dir) {
		dir = dir.norm();
		return dir - normal*dir.dot(normal)*2; // reflected
	}

	bool refract(Vec3 normal, Vec3 incident, Vec3 &result, double n) {
		incident = incident.norm();
		normal = normal.norm();
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
std::knuth_b DielectricMaterial::randomGenerator(3);

#endif