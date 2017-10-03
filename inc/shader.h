#ifndef SHADER__
#define SHADER__

#include <cmath>
#include "vec3.h"
#include "ray.h"

class Shader {
public:	
	double gama = 2;
	virtual Color getColor(Scene scene, Ray ray) = 0;
	Color correctGama(Color c) {
		c.x = std::pow(c.x, 1/gama);
		c.y = std::pow(c.y, 1/gama);
		c.z = std::pow(c.z, 1/gama);
		return c;
	}
};

#endif
