#ifndef __RENDER__
#define __RENDER__

#include "scene.h"
#include "ray.h"
#include "camera.h"

#include <stdlib.h>

class Render {
protected:
	int cols;
	int rows;
	int samples;
public: 
	Render(int cols, int rows, int samples) : cols(cols), rows(rows), samples(samples) {}
	int getCols() { return cols; }
	int getRows() { return rows; }
	virtual Color* render(Scene scene) {}
};

class DefaultRender : public Render {
public:
	DefaultRender(int cols, int rows, int samples) : Render(cols, rows, samples) {}
	
	Color* render(Scene scene) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			for(int j = 0; j < cols; j++) {
				Color c;
				for(int k = 0; k < samples; k++) {
					double v = 1 - ((double)i + drand48())/(double)rows;
					double u = ((double)j + drand48())/(double)cols;
					c = c + scene.getPixelColor(u, v, 10);
				}
				pxls[i*cols + j] = c/(double)samples;
			}
		}
		return pxls;		
	}
};

#endif