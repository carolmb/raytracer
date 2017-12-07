#ifndef PERLIN_NOISE__
#define PERLIN_NOISE__

#include <cmath>

#include "util/vec3.h"
#include "texture.h"
#include "perlin.h"

class PerlinNoise : public Texture {
	Perlin noise;
	float scale;
public:
	PerlinNoise(float scale) : Texture(), scale(scale) {
		noise = Perlin();
	}
	virtual Vec3 value(float u, float v, Vec3 p) {
		float sin = std::sin(scale*p.z);
		float t = 10*noise.turb(p);
		return Vec3(1, 1, 1)*0.5*(1 + sin + t);
	}
};

#endif