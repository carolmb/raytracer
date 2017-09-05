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
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		double t = (record.p - scene.cam.getOrigin()).len()/maxDepth;
		if(isHitting && t < 1) {
			c = fg.interpole(bg, t);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}
};

#endif