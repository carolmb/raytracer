#ifndef DEPTHSHADER__
#define DEPTHSHADER__

#include "shaders/shader.h"
#include <limits>

class DepthShader : public Shader {
public:
	double maxDepth;
	Color fg;
	Color bg;
	DepthShader(double maxDepth, Color fg, Color bg) : maxDepth(maxDepth), fg(fg), bg(bg) {}

	Color getColor(Scene scene, Ray ray) {
		Color c;
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray, std::numeric_limits<float>::max());

		double t = (record.p - ray.origin()).len()/maxDepth;
		if(isHitting && t < 1) {
			c = fg.interpole(bg, t);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}
};

#endif