#ifndef CARTOONMAT__
#define CARTOONMAT__

#include "materials/material.h"
#include <vector>

class CartoonMaterial : public Material {
public:
	std::vector<Color> gradient;
	std::vector<double> intervals;
	Color outline;

	CartoonMaterial(Color ol, std::vector<Color> g, std::vector<double> i) : outline(ol), gradient(g), intervals(i) {}
	CartoonMaterial() {}
	bool scatter(Ray r, HitRecord &rec, Vec3 &att, Ray &scattered) { return false; }
	Color getOutline() { return outline; }
	Color getColor(double cos) {
		for(int i = 0; i < intervals.size(); i++) {
			if(cos < intervals[i]) {
				return gradient[i];
			}
		}
		// cos is greater than the last value in intervals
		return gradient[gradient.size()-1];
	}
};

#endif
