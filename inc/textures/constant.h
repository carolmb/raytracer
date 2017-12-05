#ifndef CONST_TEXTURE__
#define CONST_TEXTURE__

#include "texture.h"

class ConstantTexture : public Texture {
	Vec3 color;
public:
	ConstantTexture() {}
	ConstantTexture(Vec3 vec) : color(vec) {}
	virtual Vec3 value(float u, float v, Vec3 vec) {
		return color;
	}
};

#endif