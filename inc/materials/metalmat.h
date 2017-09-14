#ifndef METALMAT__
#define METALMAT__

#include "material.h"
#include <random>

class MetalMaterial : public Material {
public:
	std::knuth_b randomGenerator;
	Vec3 kd;
	double fuzz;
	MetalMaterial(Vec3 kd, double fuzz) : kd(kd), fuzz(fuzz) {
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

	bool scatter(Ray ray, HitRecord &rec, Vec3 &att, Ray &scattered) {
		Vec3 dir = ray.dir().norm();
		Vec3 ref = dir - rec.n*dir.dot(rec.n)*2; // reflected
		scattered = Ray(rec.p + rec.n*0.01, ref + randomPoint()*fuzz);
		att = kd;
		return ref.dot(rec.n) > 0;
	}
};

#endif