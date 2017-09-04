#ifndef __NORMALSHADER__
#define __NORMALSHADER__

#include "shader.h"

class NormalRGBShader : public Shader {
	Color getColor(Scene scene, Ray ray) {
		Color c;
		
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < scene.objs.size(); k++) {
			HitRecord tempRecord;
			if(scene.objs[k]->hit(ray, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		if(hitAnything) {
			c = record.n;
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}

};

#endif