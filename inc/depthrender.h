#ifndef __DEPTHRENDER__
#define __DEPTHRENDER__

#include "render.h"

class DepthRender : public Render {
public:
	Color bgColor;
	Color fgColor;
	double maxDepth;

	DepthRender(int cols, int rows, int samples, Color fg, Color bg, double d) : 
		fgColor(fg), 
		bgColor(bg), 
		maxDepth(d),
		Render(cols, rows, samples) {}

	Color* render(Scene scene) {
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