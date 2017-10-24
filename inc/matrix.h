#ifndef MATRIX__
#define MATRIX__

class Mat4 {
	ypedef double number;
public:
	number m[4][4];
	Mat4() {}
	Mat4(number a[4][4]) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = a[i][j];
			}
		}
	}
};

#endif