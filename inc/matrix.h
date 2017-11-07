#ifndef MATRIX__
#define MATRIX__

class Mat4 {
	typedef double number;
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

	number** times(number other[4][4]) {
		number result[4][4];		
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				m[i][j] = 0;				
			}
		}
	}

};

#endif
