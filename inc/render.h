#ifndef __RENDER__
#define __RENDER__

#include "scene.h"
#include "ray.h"
#include "camera.h"
#include "shaders/shader.h"

#include <stdlib.h>

class Render {
protected:
	int cols;
	int rows;
	int samples;
	Shader *shader;
		
public: 
	Render(int cols, int rows, int samples, Shader *s) : cols(cols), rows(rows), samples(samples), shader(s) {}
	int getCols() { return cols; }
	int getRows() { return rows; }

	Color* render(Scene scene) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			for(int j = 0; j < cols; j++) {
				Color c;
				for(int k = 0; k < samples; k++) {
					double v = 1 - ((double)i + drand48())/(double)rows;
					double u = ((double)j + drand48())/(double)cols;
					c = c + shader->getColor(scene, scene.cam.getRay(u, v));
				}

				std::cout << 100 - (i*cols + j)*100/(cols*rows) << " %\r ";
				
				pxls[i*cols + j] = c/(double)samples;
			}
		}
		return pxls;		
	}
};

#endif
