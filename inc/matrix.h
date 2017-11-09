#ifndef MATRIX__
#define MATRIX__

#include <cmath>

#include "vec3.h"

class Mat4 {
	typedef double number;
public:
	number m[4][4];
	Mat4() { zeros(); }
	Mat4(number a[4][4]) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = a[i][j];
			}
		}
	}

	void identity();
	void zeros();
	void ones();

	Mat4 operator*(Mat4 o);
	Mat4 operator+(Mat4 other);
	Mat4 transpose();
	Mat4 inverse();

	double det();

	Mat4 invalid() {

	}

	Mat4 operator*(double a);

	void canonical();

	Vec3 operator*(Vec3 other);

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

};

#endif
