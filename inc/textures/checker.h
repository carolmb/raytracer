#ifndef CHECKER_TEXTURE__
#define CHECKER_TEXTURE__

#include <cmath>

#include "textures/texture.h"

class CheckerTexture : public Texture {
	Texture *even;
	Texture *odd;
public:
	CheckerTexture() {}
	CheckerTexture(Texture *t1, Texture *t2) : even(t1), odd(t2) {}
	virtual Vec3 value(float u, float v, Vec3 p) {
		float sin = std::sin(10*p.x)*std::sin(10*p.y)*std::sin(10*p.z);
		if(sin < 0) {
			return odd->value(u, v, p);
		} else {
			return even->value(u, v, p);
		}
	}
};

#endif