#ifndef __NORMALSHADER__
#define __NORMALSHADER__

#include "shader.h"

class NormalRGBShader : public Shader {
	Color getColor(Scene scene, Ray ray) {
		Color c;
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		if(isHitting) {
			c = record.n;
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}

};

#endif