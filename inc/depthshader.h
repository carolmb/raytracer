#ifndef __DEPTHSHADER__
#define __DEPTHSHADER__

#include "shader.h"

class DepthShader : public Shader {
public:
	double maxDepth;
	Color fg;
	Color bg;
	DepthShader(double maxDepth, Color fg, Color bg) : maxDepth(maxDepth), fg(fg), bg(bg) {}

	Color getColor(Scene scene, Ray ray) {
		Color c;
		
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < scene.objs.size(); k++) {
			HitRecord tempRecord;
			if(scene.objs[k]->hit(ray, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		double t = (record.p - scene.cam.getOrigin()).len()/maxDepth;
		if(hitAnything && t < 1) {
			c = fg.interpole(bg, t);
		} else {
			c = scene.backgroundColor(ray);
		}
		return c;
	}
};

#endif