#ifndef __RENDER__
#define __RENDER__

#include "scene.h"
#include "ray.h"
#include "camera.h"

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

	static Color* defaultRender(int rows, int cols, Scene scene) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			double v = 1 - i/(double)rows;
			for(int j = 0; j < cols; j++) {
				double u = j/(double)cols;
				pxls[i*cols + j] = scene.getPixelColor(u, v);
			}
		}
		return pxls;		
	}

};

#endif