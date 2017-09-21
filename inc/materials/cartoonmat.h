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
	Color getOutlineColor() { return gradient.front(); }
	Color getColor(double cos) {
		for(int i = 0; i < intervals.size() - 1; i++) {
			if(intervals[i] >= cos && cos < intervals[i+1]) {
				return gradient[i + 1];
			}
		}
		return gradient.front();
	}
	double outlineValue() { return intervals.front(); }
};

#endif
