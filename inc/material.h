#ifndef __MAT__
#define __MAT__

class Material {
public:
	Vec3 k;
	Material(Vec3 m) : k(m) {}
};

#endif