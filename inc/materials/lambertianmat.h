#ifndef LAMBMAT__
#define LAMBMAT__

#include "materials/material.h"
#include <random>

class LambertianMaterial : public Material {
public:
	std::knuth_b randomGenerator;
	Vec3 kd;
	LambertianMaterial(Vec3 kd) : kd(kd) {
		randomGenerator = std::knuth_b(3); 
	}
	
	Vec3 randomPoint() {
		Vec3 p;
		do {
			double r = std::generate_canonical<double, 6>(randomGenerator);
			double g = std::generate_canonical<double, 6>(randomGenerator);
			double b = std::generate_canonical<double, 6>(randomGenerator);
			
			p = Vec3(r, g, b)*2.0 - Vec3(1, 1, 1);
		} while(p.len2() >= 1.0);
		return p;
	}

	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) {
		Vec3 target = rec.n + randomPoint();
		scattered = Ray(rec.p, target);
		att = kd;
		return true;
	}
};

#endif