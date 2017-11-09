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

	void identity() {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				if(i == j) {
					m[i][j] = 1;
				} else {
					m[i][j] = 0;
				}				
			}
		}
	}

	void zeros() {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = 0;				
			}
		}
	}

	void ones() {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = 1;				
			}
		}
	}

	Mat4 operator*(Mat4 o) {
		number result[4][4];
		
		result[0][0] = m[0][0]*o.m[0][0] + m[0][1]*o.m[1][0] + m[0][2]*o.m[2][0] + m[0][3]*o.m[3][0]; 
		result[0][1] = m[0][0]*o.m[0][1] + m[0][1]*o.m[1][1] + m[0][2]*o.m[2][1] + m[0][3]*o.m[3][1];
		result[0][2] = m[0][0]*o.m[0][2] + m[0][1]*o.m[1][2] + m[0][2]*o.m[2][2] + m[0][3]*o.m[3][2];
		result[0][3] = m[0][0]*o.m[0][3] + m[0][1]*o.m[1][3] + m[0][2]*o.m[2][3] + m[0][3]*o.m[3][3]; 
 
 		result[1][0] = m[1][0]*o.m[0][0] + m[1][1]*o.m[1][0] + m[1][2]*o.m[2][0] + m[1][3]*o.m[3][0]; 
		result[1][1] = m[1][0]*o.m[0][1] + m[1][1]*o.m[1][1] + m[1][2]*o.m[2][1] + m[1][3]*o.m[3][1];
		result[1][2] = m[1][0]*o.m[0][2] + m[1][1]*o.m[1][2] + m[1][2]*o.m[2][2] + m[1][3]*o.m[3][2];
		result[1][3] = m[1][0]*o.m[0][3] + m[1][1]*o.m[1][3] + m[1][2]*o.m[2][3] + m[1][3]*o.m[3][3]; 

		result[2][0] = m[2][0]*o.m[0][0] + m[2][1]*o.m[1][0] + m[2][2]*o.m[2][0] + m[2][3]*o.m[3][0]; 
		result[2][1] = m[2][0]*o.m[0][1] + m[2][1]*o.m[1][1] + m[2][2]*o.m[2][1] + m[2][3]*o.m[3][1];
		result[2][2] = m[2][0]*o.m[0][2] + m[2][1]*o.m[1][2] + m[2][2]*o.m[2][2] + m[2][3]*o.m[3][2];
		result[2][3] = m[2][0]*o.m[0][3] + m[2][1]*o.m[1][3] + m[2][2]*o.m[2][3] + m[2][3]*o.m[3][3]; 
  
		result[3][0] = m[3][0]*o.m[0][0] + m[3][1]*o.m[1][0] + m[3][2]*o.m[2][0] + m[3][3]*o.m[3][0]; 
		result[3][1] = m[3][0]*o.m[0][1] + m[3][1]*o.m[1][1] + m[3][2]*o.m[2][1] + m[3][3]*o.m[3][1];
		result[3][2] = m[3][0]*o.m[0][2] + m[3][1]*o.m[1][2] + m[3][2]*o.m[2][2] + m[3][3]*o.m[3][2];
		result[3][3] = m[3][0]*o.m[0][3] + m[3][1]*o.m[1][3] + m[3][2]*o.m[2][3] + m[3][3]*o.m[3][3]; 
 
 		return Mat4(result);
	}

	Mat4 operator+(Mat4 other) {
		number result[4][4];
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				result[i][j] = m[i][j] + other.m[i][j];
			}
		}
		return Mat4(result);
	}

	Mat4 transpose() {
		Mat4 temp(m);
		temp.m[0][1] = m[1][0];
		temp.m[0][2] = m[2][0];
		temp.m[0][3] = m[3][0];
		
		temp.m[1][0] = m[0][1];
		temp.m[1][2] = m[2][1];
		temp.m[1][3] = m[3][1];

		temp.m[2][0] = m[0][2];
		temp.m[2][1] = m[1][2];
		temp.m[2][3] = m[3][2];

		temp.m[3][0] = m[0][3];
		temp.m[3][1] = m[1][3];
		temp.m[3][2] = m[2][3];

		return temp;
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

	Mat4 inverse() {
		double d = det();
		if (std::abs(d) < 0.0001) 
			return invalid();

		number cof[4][4];
		cof[0][0] = m[1][1]*m[2][2]*m[3][3] + m[1][2]*m[2][3]*m[3][1] + m[1][3]*m[2][1]*m[3][2]
			- (m[3][1]*m[2][2]*m[1][3] + m[3][2]*m[2][3]*m[1][1] + m[3][3]*m[2][1]*m[1][2]);
	    cof[0][1] = m[1][0]*m[2][2]*m[3][3] + m[1][2]*m[2][3]*m[3][0] + m[1][3]*m[2][0]*m[3][2]
			- (m[3][0]*m[2][2]*m[1][3] + m[3][2]*m[2][3]*m[1][0] + m[3][3]*m[2][0]*m[1][2]);
	    cof[0][1] *= -1;
	    cof[0][2] = m[1][0]*m[2][1]*m[3][3] + m[1][1]*m[2][3]*m[3][0] + m[1][3]*m[2][0]*m[3][1]
			- (m[3][0]*m[2][1]*m[1][3] + m[3][1]*m[2][3]*m[1][0] + m[3][3]*m[2][0]*m[1][1]);
	    cof[0][3] = m[1][0]*m[2][1]*m[3][2] + m[1][1]*m[2][2]*m[3][0] + m[1][2]*m[2][0]*m[3][1]
			- (m[3][0]*m[2][1]*m[1][2] + m[3][1]*m[2][2]*m[1][0] + m[3][2]*m[2][0]*m[1][1]);
		cof[0][3] *= -1;

	    cof[1][0] = m[0][1]*m[2][2]*m[3][3] + m[0][2]*m[2][3]*m[3][1] + m[0][3]*m[2][1]*m[3][2] 
	    	- m[3][1]*m[2][2]*m[0][3] - m[3][2]*m[2][3]*m[0][1] - m[3][3]*m[2][1]*m[0][2];
	    cof[1][0] *= -1;
	    cof[1][1] = m[0][0]*m[2][2]*m[3][3] + m[0][2]*m[2][3]*m[3][0] + m[0][3]*m[2][0]*m[3][2] 
	    	- m[3][0]*m[2][2]*m[0][3] - m[3][2]*m[2][3]*m[0][0] - m[3][3]*m[2][0]*m[0][2];
	    cof[1][2] = m[0][0]*m[2][1]*m[3][3] + m[0][1]*m[2][3]*m[3][0] + m[0][3]*m[2][0]*m[3][1] 
	    	- m[3][0]*m[2][1]*m[0][3] - m[3][1]*m[2][3]*m[0][0] - m[3][3]*m[2][0]*m[0][1];
	    cof[1][2] *= -1;
	    cof[1][3] = m[0][0]*m[2][1]*m[3][2] + m[0][1]*m[2][2]*m[3][0] + m[0][2]*m[2][0]*m[3][1] 
	    	- m[3][0]*m[2][1]*m[0][2] - m[3][1]*m[2][2]*m[0][0] - m[3][2]*m[2][0]*m[0][1];

	    cof[2][0] = m[0][1]*m[1][2]*m[3][3] + m[0][2]*m[1][3]*m[3][1] + m[0][3]*m[1][1]*m[3][2] 
	    	- m[3][1]*m[1][2]*m[0][3] - m[3][2]*m[1][3]*m[0][1] - m[3][3]*m[1][1]*m[0][2];
	    cof[2][1] = m[0][0]*m[1][2]*m[3][3] + m[0][2]*m[1][3]*m[3][0] + m[0][3]*m[1][0]*m[3][2] 
	    	- m[3][0]*m[1][2]*m[0][3] - m[3][2]*m[1][3]*m[0][0] - m[3][3]*m[1][0]*m[0][2];
	    cof[2][1] *= -1;
	    cof[2][2] = m[0][0]*m[1][1]*m[3][3] + m[0][1]*m[1][3]*m[3][0] + m[0][3]*m[1][0]*m[3][1] 
	    	- m[3][0]*m[1][1]*m[0][3] - m[3][1]*m[1][3]*m[0][0] - m[3][3]*m[1][0]*m[0][1];
	    cof[2][3] = m[0][0]*m[1][1]*m[3][2] + m[0][1]*m[1][2]*m[3][0] + m[0][2]*m[1][0]*m[3][1] 
	    	- m[3][0]*m[1][1]*m[0][2] - m[3][1]*m[1][2]*m[0][0] - m[3][2]*m[1][0]*m[0][1];
	    cof[2][3] *= -1;

	    cof[3][0] = m[0][1]*m[1][2]*m[2][3] + m[0][2]*m[1][3]*m[2][1] + m[0][3]*m[1][1]*m[2][2] 
	    	- m[2][1]*m[1][2]*m[0][3] - m[2][2]*m[1][3]*m[0][1] - m[2][3]*m[1][1]*m[0][2];
	    cof[3][0] *= -1;
	    cof[3][1] = m[0][0]*m[1][2]*m[2][3] + m[0][2]*m[1][3]*m[2][0] + m[0][3]*m[1][0]*m[2][2] 
	    	- m[2][0]*m[1][2]*m[0][3] - m[2][2]*m[1][3]*m[0][0] - m[2][3]*m[1][0]*m[0][2];
	    cof[3][2] = m[0][0]*m[1][1]*m[2][3] + m[0][1]*m[1][3]*m[2][0] + m[0][3]*m[1][0]*m[2][1] 
	    	- m[2][0]*m[1][1]*m[0][3] - m[2][1]*m[1][3]*m[0][0] - m[2][3]*m[1][0]*m[0][1];
		cof[3][2] *= -1;
		cof[3][3] = m[0][0]*m[1][1]*m[2][2] + m[0][1]*m[1][2]*m[2][0] + m[0][2]*m[1][0]*m[2][1] 
			- m[2][0]*m[1][1]*m[0][2] - m[2][1]*m[1][2]*m[0][0] - m[2][2]*m[1][0]*m[0][1];

		Mat4 inv(cof);
		inv = inv*(1/d);
		return inv.transpose();
	}

	double det() {
		double det_0_0 = m[1][1]*m[2][2]*m[3][3] + m[1][2]*m[2][3]*m[3][1] + m[1][3]*m[2][1]*m[3][2];
		det_0_0 -= m[3][1]*m[2][2]*m[1][3] + m[3][2]*m[2][3]*m[1][1] + m[3][3]*m[2][1]*m[1][2];
		
		double det_0_1 = m[1][0]*m[2][2]*m[3][3] + m[1][2]*m[2][3]*m[3][0] + m[1][3]*m[2][0]*m[3][2];
		det_0_1 -= m[3][0]*m[2][2]*m[1][3] + m[3][2]*m[2][3]*m[1][0] + m[3][3]*m[2][0]*m[1][2];
		
		double det_0_2 = m[1][0]*m[2][1]*m[3][3] + m[1][1]*m[2][3]*m[3][0] + m[1][3]*m[2][0]*m[3][1];
		det_0_2 -= m[3][0]*m[2][1]*m[1][3] + m[3][1]*m[2][3]*m[1][0] + m[3][3]*m[2][0]*m[1][1];
		
		double det_0_3 = m[1][0]*m[2][1]*m[3][2] + m[1][1]*m[2][2]*m[3][0] + m[1][2]*m[2][0]*m[3][1];
		det_0_3 -= m[3][0]*m[2][1]*m[1][2] + m[3][1]*m[2][2]*m[1][0] + m[3][2]*m[2][0]*m[1][1];
		
		double det = m[0][0]*det_0_0 - m[0][1]*det_0_1 + m[0][2]*det_0_2 - m[0][3]*det_0_3;
		return det;
	}

	Mat4 invalid() {

	}

	Mat4 operator*(double a) {
		Mat4 result;
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				result.m[i][j] = m[i][j]*a;
			}
		}
		return result;
	}

	void canonical() {
		zeros();
		m[3][3] = 1;
	}

	Vec3 operator*(Vec3 other) {
		return Vec3(
			m[0][0]*other.x + m[0][1]*other.y + m[0][2]*other.z + m[0][3],
			m[1][0]*other.x + m[1][1]*other.y + m[1][2]*other.z + m[1][3],
			m[2][0]*other.x + m[2][1]*other.y + m[2][2]*other.z + m[2][3]);
	}

};

#endif
