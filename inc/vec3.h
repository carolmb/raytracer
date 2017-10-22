#ifndef VEC3__
#define VEC3__

#include <cmath>
#include <iostream>

class Vec3 {
	typedef double number;
public:
	number x;
	number y;
	number z;

	Vec3() : x(0), y(0), z(0) {}
	Vec3(number x0, number y0, number z0) : x(x0), y(y0), z(z0) {}

	Vec3 operator+(Vec3 other) { return Vec3(x + other.x, y + other.y, z + other.z); }
	Vec3 operator-(Vec3 other) { return Vec3(x - other.x, y - other.y, z - other.z); }
	Vec3 operator*(Vec3 other) { return Vec3(x*other.x, y*other.y, z*other.z); }
	void operator+=(Vec3 other) { x += other.x; y += other.y, z += other.z; }
	
	Vec3 operator-() { return Vec3(-x, -y, -z); }
	Vec3 operator+(double a) { return Vec3(x + a, y + a, z + a); }
	Vec3 operator*(double a) { return Vec3(x*a, y*a, z*a); }
	Vec3 operator/(double a) { return Vec3(x/a, y/a, z/a); }

	double dot(Vec3 other) { return x*other.x + y*other.y + z*other.z; }
	double len2() { return x*x + y*y + z*z; }
	double len() { return std::sqrt(len2()); }
	Vec3 norm() { return Vec3(x/len(), y/len(), z/len()); }

	Vec3 interpole(Vec3 other, double t) { 
		number r = x*(1-t) + other.x*t;
		number g = y*(1-t) + other.y*t;
		number b = z*(1-t) + other.z*t;
		return Vec3(r, g, b); 
	}

	//AxB = (AyBz − AzBy, AzBx − AxBz, AxBy − AyBx)
	Vec3 cross(Vec3 other) {
		return Vec3(y*other.z - z*other.y, z*other.x - x*other.z, x*other.y - y*other.x);
	}

	friend std::ostream &operator<<(std::ostream &os, Vec3 const &v) {
		os << v.x << " " << v.y << " " << v.z << std::endl;
		return os;
	}

};

typedef Vec3 Point3;
typedef Vec3 Color;

#endif