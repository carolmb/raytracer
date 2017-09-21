#ifndef CARTOONMAT__
#define CARTOONMAT__

#include "material.h"
#include <vector>

class CartoonMaterial : public Material {
public:
	std::vector<Vec3> gradient;
	std::vector<double> intervals;

	CartoonMaterial(std::vector<Vec3> g, std::vector<double> i) : gradient(g), intervals(i) {}
	CartoonMaterial() {}
	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) { return false; }
	Color getOutline() { return gradient.front(); }
	Color getColor(double cos) {
		for(int i = 1; i < intervals.size(); i++) {
			if(cos < intervals[i]) {
				return gradient[gradient.size() - i];
			}
		}
		return gradient[1];
	}
};

#endif
