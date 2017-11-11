#ifndef TRANSF__
#define TRANSF__

#include "mat4.h"

struct Transformation {
	Mat4 mat;
	Mat4 inv;
};

#endif