#ifndef TEXTURE__
#define TEXTURE__

class Texture {
public:
	virtual Vec3 value(float u, float v, Vec3 vec) = 0;
};

#endif