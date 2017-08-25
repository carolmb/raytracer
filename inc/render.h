#ifndef __RENDER__
#define __RENDER__

#include "scene.h"
#include "ray.h"
#include "camera.h"

#include <stdlib.h>

class Render {
public:
	static Color* gradient4(int rows, int cols, Color c1, Color c2, Color c3, Color c4) {
		Color* pxls = new Color[rows*cols];
		
		for(int i = 0; i < rows; i++) {
			double ty = i/(double)(rows - 1);
			for(int j = 0; j < cols; j++) {
				double tx = j/(double)(cols - 1);
				Color top = c1.interpole(c2, tx);
				Color bottom = c3.interpole(c4, tx);
				Color final = top.interpole(bottom, ty);
				pxls[i*cols + j] = final;
			}
		}
		return pxls;
	}

	static Color* defaultRender(int rows, int cols, Scene scene, int samples) {
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

#endif