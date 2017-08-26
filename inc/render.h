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
public: 
	Render(int cols, int rows) : cols(cols), rows(rows) {}
	int getCols() { return cols; }
	int getRows() { return rows; }
	virtual Color* render(Scene scene, int samples) {}
};

class DefaultRender : public Render {
public:
	DefaultRender(int cols, int rows) : Render(cols, rows) {}
	
	Color* render(Scene scene, int samples) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			for(int j = 0; j < cols; j++) {
				Color c;
				for(int k = 0; k < samples; k++) {
					double v = 1 - ((double)i + drand48())/(double)rows;
					double u = ((double)j + drand48())/(double)cols;
					c = c + scene.getPixelColor(u, v);
				}
				pxls[i*cols + j] = c/(double)samples;
			}
		}
		return pxls;		
	}
};

class DepthRender : public Render {
public:
	Color bgColor;
	Color fgColor;
	double maxDepth;

	DepthRender(int cols, int rows, Color fg, Color bg, double d) : 
		fgColor(fg), 
		bgColor(bg), 
		maxDepth(d),
		Render(cols, rows) {}

	Color* render(Scene scene, int samples) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			for(int j = 0; j < cols; j++) {
				Color c;
				for(int k = 0; k < samples; k++) {
					double v = 1 - ((double)i + drand48())/(double)rows;
					double u = ((double)j + drand48())/(double)cols;
					c = c + scene.getPixelColorWithDepth(u, v, maxDepth, fgColor, bgColor);
				}
				pxls[i*cols + j] = c/(double)samples;
			}
		}
		return pxls;		
	}
};

#endif