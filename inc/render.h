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

	static Color backgroundColor(Ray r) {
		Vec3 unitDir = r.dir().norm();
		double t = 0.5*(unitDir.y + 1);
		return Color(0.5, 0.7, 1).interpole(Color(1, 1, 1), t);
	}

	static Color* defaultRender(int rows, int cols, Scene scene) {
		Color* pxls = new Color[rows*cols];

		for(int i = rows - 1; i >= 0; i--) {
			double v = 1 - i/(double)rows;
			for(int j = 0; j < cols; j++) {
				double u = j/(double)cols;
				Ray r = scene.cam.getRay(u, v);
				Color c;
				if(scene.sphere.hit(r)) {
					c = Color(1, 0, 0);
				} else {
					c = backgroundColor(r);
				}
				pxls[i*cols + j] = c;
			}
		}
		return pxls;		
	}

};

#endif