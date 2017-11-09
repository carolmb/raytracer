#ifndef VEC4__
#define VEC4__

#include <cmath>
#include <iostream>

#include "vec3.h"

class Vec4 {
	typedef double number;
public:
	number x;
	number y;
	number z;
	number w;

	Vec4() : x(0), y(0), z(0), w(0) {}
	Vec4(number x0, number y0, number z0, number w0) : x(x0), y(y0), z(z0), w(w0) {}

	Vec4 operator+(Vec4 other) { return Vec4(x + other.x, y + other.y, z + other.z, w + other.w); }
	Vec4 operator-(Vec4 other) { return Vec4(x - other.x, y - other.y, z - other.z, w - other.w); }
	Vec4 operator*(Vec4 other) { return Vec4(x*other.x, y*other.y, z*other.z, w*other.w); }
	void operator+=(Vec4 other) { x += other.x; y += other.y, z += other.z; w += other.w; }
	
	Vec4 operator-() { return Vec4(-x, -y, -z, -w); }
	Vec4 operator+(double a) { return Vec4(x + a, y + a, z + a, w + a); }
	Vec4 operator*(double a) { return Vec4(x*a, y*a, z*a, w*a); }
	Vec4 operator/(double a) { return Vec4(x/a, y/a, z/a, w/a); }

	double len2() { return x*x + y*y + z*z + w*w; }
	double len() { return std::sqrt(len2()); }
	Vec4 norm() { double l = len(); return Vec4(x/l, y/l, z/l, w/l); }

	friend std::ostream &operator<<(std::ostream &os, Vec4 const &v) {
		os << v.x << " " << v.y << " " << v.z << " " << v.w << std::endl;
		return os;
	}

	Vec3 toVec3() {
		return Vec3(x/w, y/w, z/w);
	}

	static Vec4 toVec4(Vec3 v) {
		return Vec4(v.x, v.y, v.z, 0);
	}

	static Vec4 toVec4Homo(Vec3 v) {
		return Vec4(v.x, v.y, v.z, 1);
	}

};

#endif