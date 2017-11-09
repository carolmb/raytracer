#ifndef TRANSF__
#define TRANSF__

#include "matrix.h"

struct Transformation {
	Mat4 mat;
	Mat4 inv;
};

#endif