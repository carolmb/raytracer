#ifndef NORMALSHADER__
#define NORMALSHADER__

#include "shader.h"
#include <limits>

class NormalRGBShader : public Shader {
	Color getColor(Scene scene, Ray ray) {
		Color c;
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray, std::numeric_limits<float>::max());

		if(isHitting) {
			c = (record.n + 1)/2;
		} else {
			c = scene.backgroundColor(ray);
		}
		return c;
	}

};

#endif