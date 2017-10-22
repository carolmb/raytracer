#ifndef RENDER__
#define RENDER__

#include "scene.h"
#include "ray.h"
#include "camera.h"
#include "shader.h"

#include <iostream>

class Render {
protected:
	int cols;
	int rows;
	int samples;
	Shader *shader;
public: 
	Render(int cols, int rows, int samples, Shader *s) : 
		cols(cols), rows(rows), samples(samples), shader(s) {}
	int getCols() { return cols; }
	int getRows() { return rows; }
	Color* render(Scene scene);
};

#endif
