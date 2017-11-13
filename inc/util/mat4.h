#ifndef MATRIX__
#define MATRIX__

#include <cmath>

#include "vec3.h"

class Mat4 {
	typedef double number;
public:
	number m[4][4];
	Mat4() { 
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = 0;
			}
		}
	}
	Mat4(number a[4][4]) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = a[i][j];
			}
		}
	}

	static Mat4 identity();
	static Mat4 zeros();
	static Mat4 ones();
	
	Mat4 transpose();
	Mat4 inverse();
	Mat4 operator*(Mat4 o);
	Mat4 operator+(Mat4 other);
	Mat4 operator*(double a);	
	Vec3 operator*(Vec3 other);
	Vec3 transfVec(Vec3 other);

	double det();

	Mat4 invalid() {

	}

	friend std::ostream &operator<<(std::ostream &os, Mat4 const &mat) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				os << mat.m[i][j] << " ";
			}
			os << std::endl;
		}
		return os;
	}

	void operator=(Mat4 other) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = other.m[i][j];
			}
		}
	}

	static Mat4 rotation(Vec3 t);
	static Mat4 translation(Vec3 t);
	static Mat4 scaling(Vec3 t);
};

#endif
